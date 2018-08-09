import sensor, image, time
from pyb import UART, LED
robot = 1

# (L Min, L Max, A Min, A Max, B Min, B Max)
if robot == 1:
    ball = [(42,60,55,79,17,58)]#[(43,69,33,73,-1,45)]
    blueGoal = [(43,48,-17,5,-49,-25)]#[(28,40,0,62,-90,-30)]
    yellowGoal = [(64,77,-25,13,32,63)]#[(72,86,-24,18,23,67)]
else:
    ball = [(50, 65, 49, 95, 10, 74)]#[(55, 70, 36, 73, 5, 49)]
    blueGoal = [(28, 64, -18, 10, -63, -21)]#[(36, 54, -26, 8, -47, -18)]
    yellowGoal = [(64, 75, -23, 29, 19, 73)]#[(71,95,-25,24,10,78)]

uart = UART(3, 9600, timeout_char = 1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_windowing((40,0,240,240))

LED(1).on()
time.sleep(100)
LED(1).off()
sensor.set_saturation(3)
sensor.set_brightness(0)
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
    #img.draw_cross(120,120)
    ballBlob = largestBlob(img.find_blobs(ball))
    blueBlob = largestBlob(img.find_blobs(blueGoal,x_stride=6,y_stride=4,merge=True,margin=34,area_threshold=15))
    yellowBlob = largestBlob(img.find_blobs(yellowGoal,x_stride=6,y_stride=4,merge=True,margin=34,area_threshold=15))

    if ballBlob:
        # Enable the line below upon calibration
        #img.draw_line((120, 120, ballBlob.cx(), ballBlob.cy()))
        print((((ballBlob.cx()-160)**2+(ballBlob.cy()-120)**2)**0.5),(255,165,0))
        sendBuffer[1] = ballBlob.cx()
        sendBuffer[2] = ballBlob.cy()

    if blueBlob:
        #print((((blueBlob.cx()-105)**2+(blueBlob.cy()-105)**2)**0.5))
        #img.draw_rectangle(blueBlob.x(),blueBlob.y(),blueBlob.w(),blueBlob.h())
        sendBuffer[3] = blueBlob.cx()
        sendBuffer[4] = blueBlob.cy()

    if yellowBlob:
        img.draw_rectangle(yellowBlob.x(),yellowBlob.y(),yellowBlob.w(),yellowBlob.h())
        sendBuffer[5] = yellowBlob.cx()
        sendBuffer[6] = yellowBlob.cy()

    for i in sendBuffer:
        try:
            uart.writechar(i)
        except Exception as E:
            print(E)
    #print(clock.fps())
