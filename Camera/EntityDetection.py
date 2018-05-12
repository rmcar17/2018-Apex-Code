import sensor, image, time
from pyb import UART, LED

# (L Min, L Max, A Min, A Max, B Min, B Max)
ball = [(33, 50, 10, 42, 31, 55)]
blueGoal = [(41, 50,-8,-4,-22,-15)]
yellowGoal = [(61,70,-3,10,15,32)]

uart = UART(3, 9600, timeout_char = 1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

LED(1).on()
time.sleep(200)
LED(1).off()
#sensor.set_saturation(3)
#sensor.set_brightness(1)

#clock = time.clock()
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

    ballBlob = largestBlob(img.find_blobs(ball,roi=(27,0,252,240),x_stride=3,y_stride=3))
    blueBlob = largestBlob(img.find_blobs(blueGoal,roi=(27,0,252,240),x_stride=8,y_stride=4))
    yellowBlob = largestBlob(img.find_blobs(yellowGoal,roi=(27,0,252,240),x_stride=8,y_stride=4))

    if ballBlob:
        img.draw_cross(ballBlob.cx(), ballBlob.cy())
        print((((ballBlob.cx()-160)**2+(ballBlob.cy()-120)**2)**0.5)*50/237)
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
    for i in sendBuffer:
        try:
            uart.writechar(i)
        except Exception as E:
            print(E)
    #print(clock.fps())
