output images for video can be found here.

Convert with:
	mogrify *.ppm --format jpg

Create video with:
	ffmpeg -framerate 30 -i output_%05d000.jpg -c:v libx264 -r 30 -pix_fmt yuv420p out.mp4