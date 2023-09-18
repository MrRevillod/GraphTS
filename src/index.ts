
import { Graph, Vertex } from "./Graph"

const main = () => {

    const G = new Graph()

    const a = new Vertex('a')
    const z = new Vertex('z')
    const s = new Vertex('s')
    const x = new Vertex('x')
    const d = new Vertex('d')
    const c = new Vertex('c')
    const f = new Vertex('f')
    const v = new Vertex('v')

    G.addVertex(a)
    G.addVertex(z)
    G.addVertex(s)
    G.addVertex(x)
    G.addVertex(d)
    G.addVertex(c)
    G.addVertex(f)
    G.addVertex(v)

    G.addEdge(s, a, 0)
    G.addEdge(s, x, 0)
    G.addEdge(a, z, 0)
    G.addEdge(x, d, 0)
    G.addEdge(x, c, 0)
    G.addEdge(d, c, 0)
    G.addEdge(d, f, 0)
    G.addEdge(c, f, 0)
    G.addEdge(c, v, 0)
    G.addEdge(f, v, 0)

    const padres = []
    const niveles = []

    const bfs = G.bfs(s, padres, niveles)

    G.showBfs(bfs)
}

main()