import spidev
import time

def rotate(tab, n):
	ntab = tab[n:] + tab[:n]
	return ntab

spi_bus=0
spi_device=0

spi=spidev.SpiDev()
spi.open(spi_bus, spi_device)
spi.max_speed_hz = 5000000

r = 115
g = 10
b = 10
rcv_byte=spi.xfer2([r, g, b])






