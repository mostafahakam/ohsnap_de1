from PIL import ImageEnhance,Image,ImageChops

class Filters():
    def __init__(self,image):
        self.img = image

    def Enhance(self):
        #Enhance
        img =  self.img
        enhancer = ImageEnhance.Contrast(img)
        Cimg = enhancer.enhance(1.4)
        enhancer = ImageEnhance.Brightness(Cimg)
        Cimg = enhancer.enhance(1.2)
        enhancer = ImageEnhance.Sharpness(Cimg)
        Cimg = enhancer.enhance(1.5)
        Cimg.save('1.jpg')

    def BW(self):
        #B&W, contrast up
        img = self.img
        Gimg = img.convert('L')
        enhancer = ImageEnhance.Brightness(Gimg)
        Gimg = enhancer.enhance(1.3)
        enhancer = ImageEnhance.Contrast(Gimg)
        Gimg = enhancer.enhance(1.4)
        Gimg.save('2.jpg')

    def custom1(self):
        #Custom
        img = self.img
        rgb2xyz = (
            0.512453,0.3575,0.18023,0,
            0.2,0.78,0.072,0,
            0.119,0.119193,0.950227,0)
        Pimg = img.convert('RGB',rgb2xyz)
        enhancer = ImageEnhance.Brightness(Pimg)
        Pimg = enhancer.enhance(1.3)
        enhancer = ImageEnhance.Contrast(Pimg)
        Pimg = enhancer.enhance(1.2)
        Pimg.save('3.jpg')
        
    def custom2(self): 
        #Custom
        img = self.img
        rgb2xyz = (
            0.812453,0.3575,0.18023,0,
            0.2,0.78,0.072,0,
            0.019,0.119193,0.950227,0)
        Pimg = img.convert('RGB',rgb2xyz)
        enhancer = ImageEnhance.Brightness(Pimg)
        Pimg = enhancer.enhance(1.1)
        enhancer = ImageEnhance.Contrast(Pimg)
        Pimg = enhancer.enhance(1.2)
        Pimg.save('4.jpg')
    def satura(self):
    #Enhance, saturation up
        img = self.img
        enhancer = ImageEnhance.Color(img)
        Cimg = enhancer.enhance(1.8)
        enhancer = ImageEnhance.Brightness(Cimg)
        Cimg = enhancer.enhance(1.2)
        enhancer = ImageEnhance.Sharpness(Cimg)
        Cimg = enhancer.enhance(1.5)
        Cimg.save('5.jpg')
