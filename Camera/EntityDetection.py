import sensor, image, time
from pyb import UART, LED

# (L Min, L Max, A Min, A Max, B Min, B Max)
ball = [(50,67,24,62,0,40)]
blueGoal = [(23,51,-18,1,-24,-8)]
yellowGoal = [(60,74,-7,15,8,48)]

uart = UART(3, 9600, timeout_char = 1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_windowing((55,15,210,210))

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
    sendBuffer = [255,0,0,0,0,0,0]

    img = sensor.snapshot()
    #img.draw_cross(105,105)
    ballBlob = largestBlob(img.find_blobs(ball))
    blueBlob = largestBlob(img.find_blobs(blueGoal,x_stride=8,y_stride=4,merge=True,margin=34,area_threshold=80))
    yellowBlob = largestBlob(img.find_blobs(yellowGoal,x_stride=8,y_stride=4,merge=True,margin=34,area_threshold=80))

    if ballBlob:
<<<<<<< HEAD
        # Enable the line below upon calibration
        #img.draw_line((105, 105, ballBlob.cx(), ballBlob.cy()))
=======
        img.draw_line((160, 120, ballBlob.cx(), ballBlob.cy()))
>>>>>>> master
        #print((((ballBlob.cx()-160)**2+(ballBlob.cy()-120)**2)**0.5))
        sendBuffer[1] = ballBlob.cx()
        sendBuffer[2] = ballBlob.cy()

    if blueBlob:
<<<<<<< HEAD
        print((((blueBlob.cx()-105)**2+(blueBlob.cy()-105)**2)**0.5))
        img.draw_line((105, 105, blueBlob.cx(), blueBlob.cy()))
        sendBuffer[3] = blueBlob.cx()
        sendBuffer[4] = blueBlob.cy()

    if yellowBlob:
        #img.draw_line((105, 105, yellowBlob.cx(), yellowBlob.cy()))
        sendBuffer[5] = yellowBlob.cx()
        sendBuffer[6] = yellowBlob.cy()
=======
        img.draw_line((160, 120, blueBlob.cx(), blueBlob.cy()))
        if blueBlob.cx() >= 255:
            sendBuffer[4] = 255
        sendBuffer[5] = blueBlob.cx() % 255
        sendBuffer[6] = blueBlob.cy()

    if yellowBlob:
        img.draw_line((160, 120, yellowBlob.cx(), yellowBlob.cy()))
        if yellowBlob.cy() >= 255:
            sendBuffer[7] = 255
        sendBuffer[8] = yellowBlob.cx() % 255
        sendBuffer[9] = yellowBlob.cy()
>>>>>>> master

    for i in sendBuffer:
        try:
            uart.writechar(i)
        except Exception as E:
            print(E)
    #print(clock.fps())
