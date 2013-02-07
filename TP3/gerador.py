def testeAliatorio():
	import random
	from string import letters
	f = open("input","w")
	for i in range (1000000):
		for j in range (4):
			f.write(random.choice(letters))
		f.write('\n')
	f.close()
	print 'Ficheiro Criado com sucesso!\n'

testeAliatorio()
