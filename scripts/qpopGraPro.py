import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time


fig = plt.figure()
fig.canvas.set_window_title('Frequenza delle Allele')
ax1 = fig.add_subplot(1,1,1)

#def animate(i):
pullData = open("Output.txt","r").read()
dataArray = pullData.split('\n')
#print dataArray[0]

lineSansT = []
vari = []
'''
x = []
f1 = []
f2 = []
'''
matrix = []


for l in dataArray:
	lineSansT.append(l.split('\t'))

for l in lineSansT[:(len(lineSansT)-1)]:
	for e in l[:(len(l)-1)]:
		y = e.split('|')
		vari.append(y)
	'''
	x.append(float(vari[0][0]))
	f1.append(float(vari[1][0]))
	f2.append(float(vari[1][1]))
	'''
	
	if(matrix == []):
		for el in vari:
			matrix.append([])
	
	#si pas de nouvelle population c est ajoute		
	if(len(matrix) == len(vari)):
		cnt = 0
		for el in vari:
			cnt2 = 0
			for ele in el:
				'''
				print len(el)-len(matrix[cnt])
				print cnt
				'''
				if(len(matrix[cnt]) < len(el)):
					for nbrCasesManquantes in range(0,len(el)-len(matrix[cnt])):
						matrix[cnt].append([])
						'''
						print "vari t: " 
						print vari
						print "matrix t: " 
						print matrix
						'''
				matrix[cnt][cnt2].append(float(ele))
				cnt2 = 1+cnt2
			cnt = 1+cnt
			
	'''		
	print "vari : " 
	print vari
	print "matrix : " 
	print matrix
	'''
	vari = []				


'''
#print x
#print f1
#print f2
print "final matrix"
print matrix
'''
	
ax1.clear()
ax1.set_ylim([0, 1])
ax1.set_xlabel("generation")
#ax1.plot(matrix[0][0],matrix[1][0])
#ax1.plot(matrix[0][0],matrix[1][1])
	
cnt3 = 0

for caselle in matrix[1:]:
	for caselline in caselle:
		ax1.plot(matrix[0][0],caselline)
#print len(matrix)
#print len(matrix[3])
#print len(matrix[1][0])
#print len(matrix[0][0][0])

bamboo = False
		
for casellinette_ in range(0,len(matrix[0][0])):
	for caselle_ in matrix[1:]:
		for caselline_ in caselle_:
			if(caselline_[casellinette_] == 0 or caselline_[casellinette_] == 1):	
				cnt3 = 1+cnt3

	if(cnt3 == 4 and bamboo == False):
		bamboo = True
		#print casellinette_
		ax1.set_xlim([0,casellinette_+10])
	#print cnt3
	cnt3 = 0

			
		




#ani = animation.FuncAnimation(fig, animate, interval=1000)
plt.show()
