from flask import Flask, render_template, request
from datetime import datetime
import serial


def convert(integer):
    if integer < 10:
        return "0" + str(integer)
    else:
        return str(integer)


app = Flask(__name__, template_folder="templates", static_folder="statics")

s = serial.Serial("/dev/tty.usbmodem1101", baudrate=9600)


@app.route('/')
def index():
    global s
    if not s.isOpen():
        s.open()

    time = datetime.now()
    hour = convert(time.hour)
    minute = convert(time.minute)

    to_write = f"S{hour}{minute}"

    print(to_write)
    s.write(to_write.encode('utf-8'))
    print("message sent");
    s.close()

    return render_template('index.html')


@app.route('/schedule', methods=["GET", "POST"])
def schedule():
    if request.method == "POST":
        global s
        if not s.isOpen():
            s.open()

        choice = str(request.form.get("choice") == "on")

        time1 = request.form.get("time1")
        time2 = request.form.get("time2")
        time3 = request.form.get("time3")

        to_write = f"{choice[0]}{time1}{time2}{time3}"
        print(to_write)
        s.write(to_write.encode('utf-8'))
        s.close()
    
        return render_template('schedule.html', choice=choice, time1=time1, time2=time2, time3=time3)


@app.route('/test')
def test():
    global s
    if not s.isOpen():
        s.open()

    s.write(b'OH-FEED-IT!')
    s.close()

    return render_template('index.html')


if __name__ == "__main__":
    app.run("0.0.0.0", port=8040)
