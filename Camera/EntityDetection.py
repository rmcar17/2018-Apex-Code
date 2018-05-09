import sensor, image, time
from pyb import UART, LED

# (L Min, L Max, A Min, A Max, B Min, B Max)
ball = [(50, 69, 35, 70, 5, 48)]
blueGoal = [(41, 50,-8,-4,-22,-15)]
yellowGoal = [(61,70,-3,10,15,32)]

uart = UART(3, 9600, timeout_char = 1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 1000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()
#LED(1).on()
def largestBlob(lBlob):
    if not lBlob:
        return None
    maxBlob = lBlob[0]
    for blob in lBlob:
        if blob.area() > maxBlob.area():
            maxBlob = blob
    return maxBlob

while(True):
    #clock.tick()
    sendBuffer = [1,0,0,0,0,0,0,0,0,0]

    img = sensor.snapshot()
    ballBlob = largestBlob(img.find_blobs(ball))
    blueBlob = largestBlob(img.find_blobs(blueGoal))
    yellowBlob = largestBlob(img.find_blobs(yellowGoal))

    if ballBlob:
        #img.draw_cross(ballBlob.cx(), ballBlob.cy())
        if ballBlob.cx() >= 255:
            sendBuffer[1] = 255
        sendBuffer[2] = ballBlob.cx() % 255
        sendBuffer[3] = ballBlob.cy()

    if blueBlob:
        #img.draw_cross(blueBlob.cx(), blueBlob.cy())
        if blueBlob.cx() >= 255:
            sendBuffer[4] = 255
        sendBuffer[5] = blueBlob.cx() % 255
        sendBuffer[6] = blueBlob.cy()

    if yellowBlob:
        #img.draw_cross(yellowBlob.cx(), yellowBlob.cy())
        if yellowBlob.cy() >= 255:
            sendBuffer[7] = 255
        sendBuffer[8] = yellowBlob.cx() % 255
        sendBuffer[9] = yellowBlob.cy()

    for i in range(1,len(sendBuffer)):
        if sendBuffer[i] == 1:
            sendBuffer[i] = 2
    #string = ""
    #LED(1).on()
    for i in sendBuffer:
        try:
            if i == 0:
                i += 1
            uart.writechar(i)
            #print(i)
        except Exception as E:
            print(E)
        #string += " "+str(i)
    #print(string)
    #LED(1).off()
    #print(clock.fps())
