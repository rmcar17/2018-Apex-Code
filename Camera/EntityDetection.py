import sensor, image, time
from pyb import UART, LED
robot = 2

# (L Min, L Max, A Min, A Max, B Min, B Max)
if robot == 1:
    ball = [(55,72,43,72,1,69)]#[(43,69,33,73,-1,45)]
    blueGoal = [(38,51,7,47,-86,-50)]#[(28,40,0,62,-90,-30)]
    yellowGoal = [(68,86,-6,38,22,68)]#[(72,86,-24,18,23,67)]
else:
    ball = [(55,70,35,67,1,49)]#[(37,70,45,74,-23,55)]
    blueGoal = [(39,53,-1,31,-66,-25)]#[(43,56,-6,48,-81,-28)]
    yellowGoal = [(57,80,-6,23,13,65)]#[(71,95,-25,24,10,78)]

uart = UART(3, 9600, timeout_char = 1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_windowing((40,0,240,240))

LED(1).on()
#time.sleep(200)
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
    img.draw_cross(120,120)
    ballBlob = largestBlob(img.find_blobs(ball))
    blueBlob = largestBlob(img.find_blobs(blueGoal,x_stride=8,y_stride=4,merge=True,margin=34,area_threshold=80))
    yellowBlob = largestBlob(img.find_blobs(yellowGoal,x_stride=8,y_stride=4,merge=True,margin=34,area_threshold=80))

    if ballBlob:
        # Enable the line below upon calibration
        img.draw_line((120, 120, ballBlob.cx(), ballBlob.cy()))
        #print((((ballBlob.cx()-160)**2+(ballBlob.cy()-120)**2)**0.5))
        sendBuffer[1] = ballBlob.cx()
        sendBuffer[2] = ballBlob.cy()

    if blueBlob:
        #print((((blueBlob.cx()-105)**2+(blueBlob.cy()-105)**2)**0.5))
        img.draw_line((120, 120, blueBlob.cx(), blueBlob.cy()))
        sendBuffer[3] = blueBlob.cx()
        sendBuffer[4] = blueBlob.cy()

    if yellowBlob:
        img.draw_line((120, 120, yellowBlob.cx(), yellowBlob.cy()))
        sendBuffer[5] = yellowBlob.cx()
        sendBuffer[6] = yellowBlob.cy()

    for i in sendBuffer:
        try:
            uart.writechar(i)
        except Exception as E:
            print(E)
    #print(clock.fps())
