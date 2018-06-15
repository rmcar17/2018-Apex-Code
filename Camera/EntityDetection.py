import sensor, image, time
from pyb import UART, LED
robot = 1

# (L Min, L Max, A Min, A Max, B Min, B Max)
if robot == 1:
    ball = [(44,61,42,73,11,63)]
    blueGoal = [(0,0,0,0,0,0)]
    yellowGoal = [(47,72,-20,-2,39,62)]
else:
    ball = [(43,55,40,78,2,55)]
    blueGoal = [(0,0,0,0,0,0)]
    yellowGoal = [(58,73,-10,10,6,53)]

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
sensor.set_saturation(3)
sensor.set_brightness(3)
sensor.set_contrast(0)

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
        # Enable the line below upon calibration
        img.draw_line((105, 105, ballBlob.cx(), ballBlob.cy()))
        #print((((ballBlob.cx()-160)**2+(ballBlob.cy()-120)**2)**0.5))
        sendBuffer[1] = ballBlob.cx()
        sendBuffer[2] = ballBlob.cy()

    if blueBlob:
        #print((((blueBlob.cx()-105)**2+(blueBlob.cy()-105)**2)**0.5))
        img.draw_line((105, 105, blueBlob.cx(), blueBlob.cy()))
        sendBuffer[3] = blueBlob.cx()
        sendBuffer[4] = blueBlob.cy()

    if yellowBlob:
        img.draw_line((105, 105, yellowBlob.cx(), yellowBlob.cy()))
        sendBuffer[5] = yellowBlob.cx()
        sendBuffer[6] = yellowBlob.cy()

    for i in sendBuffer:
        try:
            uart.writechar(i)
        except Exception as E:
            print(E)
    #print(clock.fps())
