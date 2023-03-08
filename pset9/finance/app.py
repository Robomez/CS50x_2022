import os

from cs50 import SQL
from datetime import datetime
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Which stocks the user owns, number of shares, total value of each holding
    usid = session["user_id"]
    symbols = db.execute("SELECT symbol, sum(shares) AS number from deals WHERE user_id=? GROUP BY symbol", usid)

    # Current cash balance
    cash = db.execute("SELECT cash FROM users WHERE id = ?", usid)[0]['cash']

    # Current price and total value
    name = []
    price = []
    total = []
    priceusd = []
    totalusd = []
    for count, row in enumerate(symbols):
        k = lookup(row['symbol'])
        name.append(k['name'])
        price.append(round(k['price'], 2))
        total.append(round(price[count] * row['number'], 2))
        priceusd.append(usd(price[count]))
        totalusd.append(usd(total[count]))

    grandusd = usd(round(sum(total) + cash, 2))
    cashusd = usd(round(cash, 2))

    return render_template("index.html", usid=usid, name=name, cash=cashusd, symbols=symbols, priceusd=priceusd, totalusd=totalusd, grand=grandusd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # If post method
    if request.method == "POST":

        # Ensure symbol is correct
        symbol = lookup(request.form.get("symbol"))

        usid = session["user_id"]
        if not symbol:
            return apology("no such symbol", 400)

        # Ensure number of shares not less than 0
        shares = request.form.get("shares")

        # If shares not int
        if not shares.isdigit():
            return apology("Number of shares must be an integer", 400)

        shares = int(shares)
        if shares < 0:
            return apology("shares can't be less than 0", 400)

        # Get price and name for this stock
        price = symbol['price']
        name = symbol['symbol']

        # Get how much cash user has
        cash = db.execute("SELECT cash FROM users WHERE id = ?", usid)[0]['cash']

        # Compare cash amount and cost of shares
        cost = round(price * shares, 2)
        if cost > cash:
            return apology("not enough cash to buy", 400)

        # Everythong is OK. Save to deals table time, user_id, symbol, shares, price
        db.execute("INSERT INTO deals (time, user_id, symbol, shares, price) VALUES (?, ?, ?, ?, ?);", datetime.now(), usid,
                    name, shares, price)

        # Update cash amount
        cash = round(cash - cost, 2)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, usid)

        return redirect("/")

    # If GET method
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute("SELECT time, symbol, shares, price FROM deals WHERE user_id=?", session["user_id"])
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # If post method
    if request.method == "POST":
        symbol = lookup(request.form.get("symbol"))
        if not symbol:
            return apology("No such symbol", 400)

        symbol["price"] = usd(symbol["price"])
        return render_template("quoted.html", symbol=symbol)

    # If GET method
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # If POST send data to db and render "login.html"
    if request.method == "POST":

        # Ensure username was submitted
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)

        # Ensure username doesn't already exist
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if rows:
            return apology("username already exists", 400)

        # Ensure password was submitted
        password = request.form.get("password")
        if not password:
            return apology("must provide password", 400)

        # Ensure confirmation was dubmitted
        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("must provide password duplicate", 400)

        # Ensure confirmation matches password
        if password != confirmation:
            return apology("password and duplicate doesn't match", 400)

        # If all successful
        hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        flash("You are registered!")
        return render_template("login.html")

    # If GET route to "register.html"
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    usid = session["user_id"]

    # If POST
    if request.method == "POST":

        symbols = db.execute("SELECT DISTINCT symbol FROM deals WHERE user_id= ?", usid)

        # Get symbol from select
        symsym = request.form.get("symbol")

        # If symbol not selected
        if not symsym:
            return apology("Select a symbol from list", 400)

        symbol = db.execute("SELECT DISTINCT symbol FROM deals WHERE symbol = ?", symsym)[0]

        # If this stock isn't owned by him return apology
        if symbol not in symbols:
            return apology("You don't own this stock", 400)

        # If user selects less than 0 shares
        shares = int(request.form.get("shares"))
        if shares < 0:
            return apology("shares can't be less than 0", 400)

        if not isinstance(shares, int):
            return apology("Number of shares must be an integer", 400)

        # If the user doesn't have enough shares return apology
        amount = db.execute("SELECT sum(shares) AS sum FROM deals WHERE user_id = ? AND symbol = ?", usid, symsym)[0]['sum']
        if shares > amount:
            return apology("You don't have that amount of shares", 400)

        # Everythong is OK. Save to deals table time, user_id, symbol, shares, price
        price = round(lookup(symsym)['price'], 2)
        gain = round(price * shares, 2)
        shares = shares * -1

        cash = round(db.execute("SELECT cash FROM users WHERE id = ?", usid)[0]['cash'], 2)

        db.execute("INSERT INTO deals (time, user_id, symbol, shares, price) VALUES (?, ?, ?, ?, ?);", datetime.now(), usid,
                   symsym, shares, price)

        # Update cash amount
        cash = round(cash + gain, 2)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, usid)

        return redirect("/")

    # If GET
    symbo = db.execute("SELECT symbol, sum(shares) AS sum FROM deals WHERE user_id= ? GROUP BY symbol", usid)
    return render_template("sell.html", symbols=symbo)

@app.route("/cash", methods=["POST"])
@login_required
def cash():

    cash = request.form.get("cash_input")
    # If cash not int
    if not isinstance(cash, int):
        return apology("Cash must be an integer", 400)

    # If cash < 0
    if cash < 0:
        return apology("Can't add less than 0", 400)

    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", cash, session["user_id"])

    return redirect("/")

