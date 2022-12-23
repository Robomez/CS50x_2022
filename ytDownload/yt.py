from pytube import YouTube
from sys import argv

link = argv[1]

yt = YouTube(link)

print("Title ", yt.title)

yd = yt.streams.filter(progressive=True, resolution="720p").first()

yd.download(r'/mnt/c/Users/kluyf/Desktop')
