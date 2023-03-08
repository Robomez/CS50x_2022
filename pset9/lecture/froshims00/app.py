from flask import Flask, render_template, request

app = Flask(__name__)

SPORTS = [
    "Basketball",
    "Football",
    "Soccer",
    "Frisbee"
]

REGISTRANTS = {}

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():

    name = request.form.get("name")
    sport = request.form.get("sport")
    if not name or sport not in SPORTS:
        return render_template("failure.html")
    # else: Don't need else because if if is true it returns, i.e. stops executing function
        REGISTRANTS[name] = sport

    # Confirm registration
        return render_template("success.html")

@app.route("/registrants")
def registrants():
    return render_template("registrants.html", registrants=REGISTRANTS)