#Graph Theory
#Patricia Brenny Ribeiro
#Computer Engineering undergrad
#Universidade Federal de Itajubá - MG
from math import sqrt
def distance(vet1,vet2):
	mod = sqrt(((vet2[0] - vet1[0])**2 + (vet2[1] - vet1[1])**2))
	mod = mod*100
	return mod

def generateGraph(vList):
	adjMatrix = []
	size = len(vList)
	for i in range(size):
		adjMatrix.append([])
		for j in range(size):
			x = distance(vList[i], vList[j])
			adjMatrix[i].append(x)
			#print("[%.1f]" %x, end = '')
		#print()
	return adjMatrix


def Prim(G):
	sum = 0
	noVertices = len(G[0])
	selected = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
	noEdges = 0
	selected[0] = True
	print("\n	Edge : 	Weight	\n")

	while (noEdges < noVertices - 1):
		minimum = INF
		x = 0
		y = 0
		for i in range(noVertices):
			if selected[i]:
				for j in range(noVertices):
					if ((not selected[j]) and G[i][j] != 0):
						if minimum >= G[i][j]:
							minimum = G[i][j]
							x = i
							y = j
		print(nameList[x] + " ---> " + nameList[y] + " : %.4f km" %G[x][y])
		sum += G[x][y]
		selected[y] = True
		noEdges += 1
	return sum

INF = 99999
nameList = ["Paracatu", "Montes Claros", "Teófilo Otoni", "Uberlândia", "Diamantina",
			"Governador Valadares", "Uberaba", "Divinópolis", "Belo Horizonte", "Ipatinga",
			"Manhuaçu", "Passos", "Conselheiro Lafaiete", "Muriaé", "Poços de Caldas",
			"Varginha", "Juiz de Fora", "Pouso Alegre"]
#these coordinates are in cm
vList = [(6.14, 4.00), (10.00, 3.77), (13.57, 5.31), (4.28, 6.82),(10.48, 6.18), (12.76, 6.88),
 		(4.93, 8.11), (8.62, 8.68), (10.16, 8.40), (11.92, 8.17), (12.66, 8.87), (6.29, 9.55),
		(9.93, 9.63), (12.02, 10.37), (6.77, 11.07), (8.04, 10.69), (10.48, 11.18), (7.47, 11.81)]

adjMatrix = generateGraph(vList)
sum = Prim(adjMatrix)
print("Total km: %.4f"  %sum)
