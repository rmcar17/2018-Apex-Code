import sensor, image, time
from pyb import UART, LED

camDebug = False
FPSDebug = False

robot = 2

if robot == 1:
    camThresholds = [((27, 58, 20, 97, 16, 73),), #Ball
    ((27, 41, -23, 5, -38, -16),), #Blue Goal
    ((48, 67, -4, 11, 27, 85),)]   #Yellow Goal
else:
    camThresholds = [((41, 65, 34, 80, 22, 67),),
    ((39, 50, -15, 8, -41, -14),),
    ((59, 89, -24, 25, 24, 69),)]

def largestBlob(lBlob):
    if not lBlob:
        return None
    return sorted(lBlob,key=lambda blob: blob.area())[0]

class Sender:
    def __init__(self):
        self.uart = UART(3, 9600, timeout_char = 1000)

    def sendData(self, sendBuffer):
        self.uart.writechar(255)
        for b in sendBuffer:
            self.uart.writechar(b)

class Reader:
    def __init__(self,thresholds,debugCam=False):
        self.setupCam()

        self.thresholds = thresholds
        self.debug = debugCam

    def update(self):
        img = sensor.snapshot()

        ballBlob = self.getXY(largestBlob(img.find_blobs(self.thresholds[0],x_stride=4,y_stride=4,pixels_threshold=20)))
        blueBlob = self.getXY(largestBlob(img.find_blobs(self.thresholds[1],x_stride=15,y_stride=8,merge=True,margin=34,pixels_threshold=100)))
        yellowBlob = self.getXY(largestBlob(img.find_blobs(self.thresholds[2],x_stride=15,y_stride=8,merge=True,margin=34,pixels_threshold=50)))

        if self.debug:
            if ballBlob != (255, 255):
                img.draw_line((100, 100, ballBlob[0], ballBlob[1]),color=(255,92,0),thickness=2)
            if blueBlob != (255, 255):
                img.draw_line((100, 100, blueBlob[0], blueBlob[1]),color=(0,75,255),thickness=2)
            if yellowBlob != (255, 255):
                img.draw_line((100, 100, yellowBlob[0], yellowBlob[1]),color=(255,255,0),thickness=2)

        self.data = (ballBlob[0],ballBlob[1],blueBlob[0],blueBlob[1],yellowBlob[0],yellowBlob[1])

    def getXY(self,blob):
        return (blob.cx(),blob.cy()) if blob else (254,254)

    def getData(self):
        return self.data

    def setupCam(self):
        sensor.reset()
        sensor.set_pixformat(sensor.RGB565)
        sensor.set_framesize(sensor.QVGA)
        sensor.skip_frames(time = 1000)
        sensor.set_auto_gain(False)
        sensor.set_auto_whitebal(False)
        sensor.set_windowing((60,20,200,200))

        sensor.set_saturation(3)
        sensor.set_brightness(-2)
        sensor.set_contrast(3)

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