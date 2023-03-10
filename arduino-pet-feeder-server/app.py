from flask import Flask, render_template, request
from datetime import datetime
import serial


def convert(integer):
    if integer < 10:
        return "0" + str(integer)
    else:
        return str(integer)


app = Flask(__name__, template_folder="templates", static_folder="statics")

s = serial.Serial("/dev/tty.usbmodem13301", baudrate=9600)


@app.route('/')
def index():
    now_time = datetime.now()
    hour = convert(now_time.hour)
    minute = convert(now_time.minute)

    to_write = f"S{hour}{minute}"

    print(to_write)
    s.write(to_write.encode('ascii'))
    print("message sent")

    return render_template('index.html')


@app.route('/schedule', methods=["GET", "POST"])
def schedule():
    if request.method == "POST":
        global s

        choice = str(request.form.get("choice") == "on")

        time1 = request.form.get("time1")
        time2 = request.form.get("time2")
        time3 = request.form.get("time3")

        to_write = f"{choice[0]}{time1}{time2}{time3}"
        print(to_write)
        s.write(to_write.encode('ascii'))
    
        return render_template('schedule.html', choice=choice, time1=time1, time2=time2, time3=time3)


@app.route('/test')
def test():
    global s

    message = "OPEN"
    print(f"sending message: {message}")
    s.write(message.encode('ascii'))
    print("sent")

    return render_template('index.html')


if __name__ == "__main__":
    app.run("0.0.0.0", port=8040)
