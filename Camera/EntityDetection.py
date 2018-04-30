import sensor, image, time
from pyb import UART, LED

# (L Min, L Max, A Min, A Max, B Min, B Max)
ball = [(65, 80, 25, 55, 25, 55)]
blueGoal = [(29, 35,-6,3,-23,-11)]
yellowGoal = [(49,56,-3,9,11,30)]

uart = UART(3, 9600, timeout_char = 1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()

while(True):
    sendBuffer = [1,0,0,0,0,0,0,0,0,0]

    img = sensor.snapshot()

    ballBlob = img.find_blobs(ball)
    blueBlob = img.find_blobs(blueGoal)
    yellowBlob = img.find_blobs(yellowGoal)

    if ballBlob:
        ballBlob = ballBlob[0]
        img.draw_cross(ballBlob.cx(), ballBlob.cy())
        if ballBlob.cx() >= 255:
            sendBuffer[1] = 255
        sendBuffer[2] = ballBlob.cx() % 255
        sendBuffer[3] = ballBlob.cy()

    if blueBlob:
        blueBlob = blueBlob[0]
        if blueBlob.cx() >= 255:
            sendBuffer[4] = 255
        sendBuffer[5] = blueBlob.cx() % 255
        sendBuffer[6] = blueBlob.cy()

    if yellowBlob:
        yellowBlob = yellowBlob[0]
        if yellowBlob.cy() >= 255:
            sendBuffer[7] = 255
        sendBuffer[8] = yellowBlob.cx() % 255
        sendBuffer[9] = yellowBlob.cy()

    for i in range(1,len(sendBuffer)):
        if sendBuffer[i] == 1:
            sendBuffer[i] = 2
    string = ""
    LED(1).on()
    for i in sendBuffer:
        try:
            if i == 0:
                i += 10
            uart.writechar(i)
            #print(i)
        except Exception as E:
            print(E)
        string += " "+str(i)
    print(string)
    #LED(1).off()
    #print(clock.fps())
