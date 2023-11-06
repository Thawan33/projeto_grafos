grafo = []

qtd_vertices = int(input("Quantos vértices tem o grafo? "))
    
for i in range(qtd_vertices):
    grafoAux = []
    contador = 1
    while contador == 1:
        aresta = int(input(f'Qual o vértice adjacente de {i}: '))
        if aresta < 0:
            contador = 0
        else:
            grafoAux.append(aresta)
        
    grafo.append(grafoAux)

print(grafo)