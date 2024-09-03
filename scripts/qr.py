import segno

def make_qr(url, image):
    qr = segno.make_qr(url)
    qr.save(image, scale=16)

make_qr("https://southernmethodistuniversity.github.io/parallel_cpp/intro.html", 
        "../docs/parallel_cpp_qr.png")

