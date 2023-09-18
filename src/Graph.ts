
import { Edge, Nivel, Padre, Frontera } from "./Interfaces"

class Graph {

    vertices: Vertex[]

    constructor() {
        this.vertices = []
    }

    show() {

        console.log()

        for (const vertex of this.vertices) {
            for (const { to, weight } of vertex.edges) {
                console.log(`${vertex.name} -> ${weight} -> ${to.name}`)
            }
        }

        console.log()
    }

    addVertex(vertex: Vertex) {

        if (this.vertices.find(v => v.name === vertex.name)) {
            throw { message: 'El vértice ya existe' }
        }

        this.vertices.push(vertex)
    }

    removeVertex(name: string) {

        const vertex = this.vertices.find(v => v.name === name)

        if (!vertex) {
            throw { message: 'El vértice no existe' }
        }

        this.vertices = this.vertices.filter(v => v !== vertex)

        for (const v of this.vertices) {
            v.edges = v.edges.filter(edge => edge.to !== vertex)
        }
    }

    addEdge(from: Vertex, to: Vertex, weight: number) {

        if (from === to) {
            throw { message: 'Un vertice no puede estar conectado a si mismo' }
        }

        if (!this.vertices.includes(from) || !this.vertices.includes(to)) {
            throw { message: 'El vertice no existe en el grafo' }
        }

        from.edges.forEach((edge) => {
            if (edge.to === to) {
                throw { message: 'La arista ya existe' }
            }
        })

        to.edges.forEach((edge) => {
            if (edge.to === from) {
                throw { message: 'La arista ya existe' }
            }
        })

        from.edges.push({ to, weight })
    }

    bfs(s: Vertex, padres: Padre[], niveles: Nivel[]) {

        let frontera = new Frontera()

        niveles.push({ vertex: s, distance: 0 })
        padres.push({ vertex: s, padre: null })

        frontera.push(s)

        let i = 1

        while (!frontera.isEmpty()) {

            const next = new Frontera()

            for (const u of frontera.vertices) {

                for (const { to } of u.edges) {

                    if (!niveles.some(({ vertex }) => vertex === to)) {

                        niveles.push({ vertex: to, distance: i })
                        padres.push({ vertex: to, padre: u })

                        next.push(to)
                    }
                }
            }

            frontera = next
            i++
        }

        return niveles
    }

    showBfs(niveles: Nivel[]) {

        for (const { vertex, distance } of niveles) {
            console.log(`${vertex.name} -> ${distance}`)
        }
    }

    dfs(s: Vertex, padres: Padre[]) {

        padres.push({ vertex: s, padre: null })

        for (const { to } of s.edges) {

            if (!padres.some(({ vertex }) => vertex === to)) {

                padres.push({ vertex: to, padre: s })
                this.dfs(to, padres)
            }
        }

        return padres
    }

    showDfs(padres: Padre[]) {

        for (const { vertex, padre } of padres) {
            console.log(`${vertex.name} -> ${padre?.name}`)
        }
    }
}

class Vertex {

    name: string
    edges: Edge[]

    constructor(name: string) {
        this.name = name
        this.edges = []
    }
}

export { Graph, Vertex }
