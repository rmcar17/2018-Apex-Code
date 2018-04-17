import sensor, image, time
from pyb import UART, LED

# (L Min, L Max, A Min, A Max, B Min, B Max)
ball = [(38, 55, 32, 66, 17, 50)]
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
        if ballBlob.x() >= 255:
            sendBuffer[1] = 255
        sendBuffer[2] = ballBlob.x() % 255
        sendBuffer[3] = ballBlob.y()

    if blueBlob:
        blueBlob = blueBlob[0]
        if blueBlob.x() >= 255:
            sendBuffer[4] = 255
        sendBuffer[5] = blueBlob.x() % 255
        sendBuffer[6] = blueBlob.y()

    if yellowBlob:
        yellowBlob = yellowBlob[0]
        if yellowBlob.y() >= 255:
            sendBuffer[7] = 255
        sendBuffer[8] = yellowBlob.x() % 255
        sendBuffer[9] = yellowBlob.y()

    for i in range(1,len(sendBuffer)):
        if sendBuffer[i] == 1:
            sendBuffer[i] = 2

    LED(1).on()
    for i in sendBuffer:
        uart.writechar(i)
    LED(1).off()
    #print(clock.fps())
