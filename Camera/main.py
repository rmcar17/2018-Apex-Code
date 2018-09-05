import sensor, image, time
from pyb import UART, LED

camDebug = False
FPSDebug = True

robot = 2

if robot == 1:
    camThresholds = [((27, 58, 20, 97, 16, 73),), #Ball
    ((27, 41, -23, 5, -38, -16),), #Blue Goal
    ((48, 67, -4, 11, 27, 85),)]   #Yellow Goal
else:
    camThresholds = [((60, 72, 38, 61, 5, 39),),
    ((57, 60, -14, -10, -27, -24),),
    ((68, 82, 1, 15, 20, 52),)]

def findBlobs(img,thresholds):


def largestBlob(lBlob):
    if not lBlob:
        return None
    return sorted(lBlob,key=lambda blob: blob.area())[0]

class Sender:
    def __init__(self):
        self.uart = UART(3, 9600, timeout_char = 1000)

    def sendData(self, sendBuffer):
        for b in sendBuffer:
            self.uart.writechar(b)

class Reader:
    def __init__(self,thresholds,debugCam=False):
        self.setupCam()

        self.thresholds = thresholds
        self.clock = time.clock()

    def update(self):
        self.img = sensor.snapshot()

        ballBlob = self.getXY(largestBlob(self.img.find_blobs(self.thresholds[0])))
        blueBlob = self.getXY(largestBlob(self.img.find_blobs(self.thresholds[1],x_stride=6,y_stride=4,merge=True,margin=34,area_threshold=15)))
        yellowBlob = self.getXY(largestBlob(self.img.find_blobs(self.thresholds[2],x_stride=6,y_stride=4,merge=True,margin=34,area_threshold=15)))

        self.data = (ballBlob[0],ballBlob[1],blueBlob[0],blueBlob[1],yellowBlob[0],yellowBlob[1])

    def getXY(self,blob):
        return (blob.cx(),blob.cy()) if blob else (0,0)

    def getData(self):
        return self.data

    def setupCam(self):
        sensor.reset()
        sensor.set_pixformat(sensor.RGB565)
        sensor.set_framesize(sensor.QVGA)
        sensor.skip_frames(time = 2000)
        sensor.set_auto_gain(False)
        sensor.set_auto_whitebal(False)
        sensor.set_windowing((40,0,240,240))

        sensor.set_saturation(1)
        sensor.set_brightness(-1)
        sensor.set_contrast(0)

        LED(1).on()
        time.sleep(100)
        LED(1).off()


send = Sender()
cam = Reader(camThresholds,debugCam=camDebug)

clock = time.clock()

while True:
    cam.update()
    send.sendData(cam.getData())

    if FPSDebug:
        print(clock.fps())
        clock.tick()
