#  Implements a registration form, storing registrants in a SQLite DB, with support for registration

from cs50 import SQL
from flask import Flask, render_template, request, redirect

app = Flask(__name__)

db = SQL("sqlite:///froshims.db")

REGISTRANTS = {}

SPORTS = [
    "Basketball",
    "Soccer",
    "Frisbee"
]


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/deregister", methods=["POST"])
def deregister():

    # Forget registrant
    id = request.form.get("delete_id")
    if id:
        db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/registrants")


@app.route("/register", methods=["POST"])
def register():

    # Validate name
    name = request.form.get("name")
    sport = request.form.get("sport")
    if not name or sport not in SPORTS:
        return render_template("failure.html")

    # Remember registrant
    db.execute("INSERT INTO registrants (name, sport) VALUES (?,?)", name, sport)

    # Confirm registration
    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    # Get registrants from the db
    registrants = db.execute("SELECT * FROM registrants")
    # Open registrants.html with db data loaded into memory
    return render_template("registrants.html", registrants=registrants)
