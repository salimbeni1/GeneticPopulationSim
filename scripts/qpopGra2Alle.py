import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time


fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

def animate(i):
	pullData = open("Output.txt","r").read()
	dataArray = pullData.split('\n')
	#print dataArray[0]

	lineSansT = []
	vari = []
	x = []
	f1 = []
	f2 = []


	for l in dataArray:
		lineSansT.append(l.split('\t'))


	for l in lineSansT[0:(len(lineSansT)-1)]:
		for e in l:
			y = e.split('|')
			vari.append(y)
		x.append(float(vari[0][0]))
		f1.append(float(vari[1][0]))
		f2.append(float(vari[1][1]))
		vari = []


	#print x
	#print f1
	#print f2
	
	ax1.clear()
	ax1.set_ylim([0, 1])
	ax1.plot(x,f1)
	ax1.plot(x,f2)

ani = animation.FuncAnimation(fig, animate, interval=1000)
plt.show()
