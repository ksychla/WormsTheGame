import re

def main():
	with open('terrain.obj', 'r') as file:
		f = file.read()
	f = re.split('\ |\n',f)
	f.remove('')
	verts = 0
	vertsTab = []
	normalsTab = []
	flagaVerts = 0
	flagaNorm = 0
	suma = 0
	flagaFace = 0
	positionTab = []
	posNormTab = []
	for i in f:
		if i == 'v':
			verts += 1
			flagaVerts = 3
			continue
		if flagaVerts > 0:
			flagaVerts -= 1
			vertsTab.append(i)
		if i == 'vn':
			flagaNorm = 3
			suma += 1
			continue
		if flagaNorm > 0:
			flagaNorm -= 1
			normalsTab.append(i)
		if i == 'f':
			flagaFace = 3
			continue
		if flagaFace > 0:
			flagaFace -= 1
			temp = i.split("//")
			positionTab.append(temp[0])
			posNormTab.append(temp[1])
	with open("Terrain.h", "w") as file:
		file.write("unsigned int terrainVertexCount="+str(verts))
		file.write("\n\nfloat terrainVertices[]={")
		t = True
		for i in vertsTab:
			if t:
				t = False
				file.write(str(i))
			else:
				file.write(", "+str(i))
		file.write("};\n\n")
		file.write("float terrainNormals[]={")
		t = True
		for i in normalsTab:
			if t:
				t = False
				file.write(str(i))
			else:
				file.write(", "+str(i))
		file.write("};\n\n")

		file.write("int terrainPosition[]={")
		t = True
		for i in positionTab:
			if t:
				t = False
				file.write(str(i))
			else:
				file.write(", "+str(i))
		file.write("};\n\n")
		file.write("int terrainNormalsPosition[]={")
		t = True
		for i in posNormTab:
			if t:
				t = False
				file.write(str(i))
			else:
				file.write(", "+str(i))
		file.write("};\n\n")
if __name__ == '__main__':
	main()
