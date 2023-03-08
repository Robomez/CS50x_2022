#  Implements a registration form, sconfirming registration via email

import os
import re

from flask import Flask, render_template, request
from flask_mail import Mail, Message

app = Flask(__name__)

# Requires that "Less secure app access" be on
# https://support.google.com/accounts/answer/6010255
# app.config is a special dictionary that comes with flask
# os.environ dictionary refers to an environment dict. Like out-of-band pairs in the comp memory. So that they are not stored in code.
app.config["MAIL_DEFAULT_SENDER"] = os.environ["MAIL_DEFAULT_SENDER"]
app.config["MAIL_PASSWORD"] = os.environ["MAIL_PASSWORD"]
app.config["MAIL_PORT"] = 587
app.config["MAIL_SERVER"] = "smtp.gmail.com"
# Use encryption
app.config["MAIL_USE_TLS"] = True
app.config["MAIL_USERNAME"] = os.environ["MAIL_USERNAME"]
mail = Mail(app)

SPORTS = [
    "Basketball",
    "Soccer",
    "Frisbee"
]


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():

    # Validate submission
    name = request.form.get("name")
    sport = request.form.get("sport")
    email = request.form.get("email")
    if not name or not email or sport not in SPORTS:
        return render_template("failure.html")

    # Send mail
    message = Message("You are registered!", recipients=[email])
    mail.send(message)

    # Confirm registration
    return render_template("success.html")
