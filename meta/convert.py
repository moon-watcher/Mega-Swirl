#!/usr/bin/python

"""
	This entire thing sucks and is generally horrible.
	
	A ticket will be put in for its expansion and rewrite.
"""
from PIL import Image
import sys, binascii, struct

"""
	Splits a string by n characters
"""
def split_by_n(arr, num):
	return [arr[i:i+num] for i in range(0, len(arr), num)]

"""
	Get the sega colour for the given string hex segment
"""
def get_sega_colour(col):
	return int(''.join([ '0', col[0], col[2], col[4] ]), 16)

	
"""
	Pad value to nearest multiple of 8. If value / 8 is not a whole number,
	then add whatever is required.
"""
def pad_to_multiple(val):
	remaining = val % 8
	if not remaining == 0:
		val = val + ( 8 - remaining )
	return val

"""
	Constants
"""
COMPRESSION = {
	'NONE': '00',
	'RLE': '01'
}
ORDER = {
	'TILE': '00',
	'SPRITE': '01'
}

if len(sys.argv) > 1:
	inputfn = sys.argv[1]
	
	if len(sys.argv) > 2:
		option = sys.argv[2]
	else:
		option = None
else:
	print "CONVERT.PY crude version: Please enter a filename."
	sys.exit(0)

print "CONVERT.PY crude version - Converting " + inputfn
image = Image.open(inputfn)
pixel_map = image.load()
segments = split_by_n( binascii.hexlify(image.palette.palette) , 6)
sega_segments = []
for segment in segments:
	sega_segments.append(
		binascii.hexlify( struct.pack( '>H', get_sega_colour(segment) ) )
	)
# Sega colour segments should be no shorter than 16 elements
if len(sega_segments) < 16:
	for i in range(0, 16 - len(sega_segments)):
		sega_segments.append('0000')
compression = COMPRESSION['NONE']
sprite_order = ORDER['SPRITE'] if option == "-s" else ORDER['TILE']
sega_bytes = []
outfilename = inputfn.split('.')[0] + '.gia'

print "Converting for " + ( "sprite" if sprite_order == ORDER['SPRITE'] else "tile" ) + " order"
print "Image Color Segments: " + str(segments)
print "Sega Color Segments:  " + str(sega_segments)
print "Image size:           " + str(image.size)

if sprite_order == ORDER['TILE']:
	for tileY in range(0, image.size[1], 8):
		for tileX in range(0, image.size[0], 8):
			#individual tiles	
			for y in range(tileY, tileY + 8):
				sega_row = ''
				
				for x in range(tileX, tileX + 8):
					sega_row = sega_row + format(pixel_map[x, y], 'x')

				sega_bytes.append(sega_row)
else:
	for tileX in range(0, image.size[0], 8):
		for tileY in range(0, image.size[1], 8):
			#individual tiles	
			for y in range(tileY, tileY + 8):
				sega_row = ''
				
				for x in range(tileX, tileX + 8):
					sega_row = sega_row + format(pixel_map[x, y], 'x')

				sega_bytes.append(sega_row)

with open(outfilename, 'wb') as f:
	# Write header
	f.write( struct.pack('>I', 0xB16D1CC5) )
	
	# Write options
	# Compression and sprite order
	f.write( struct.pack('B', int( compression, 16 ) ) )
	f.write( struct.pack('B', int( sprite_order, 16 ) ) )
	# Tiles - X direction
	f.write( struct.pack('B', image.size[0] // 8 ) )
	# Tiles - Y direction
	f.write( struct.pack('B', image.size[1] // 8 ) )
	
	# No support for metadata in this version
	f.write( struct.pack('>I', 0x00000000) )
	
	# Write palette
	for entry in sega_segments:
		f.write( 
			struct.pack('>H', int( entry, 16 ) ) 
		)

	# Write entries
	for entry in sega_bytes:
		f.write(
			struct.pack('>I', int( entry, 16 ) )
		)
