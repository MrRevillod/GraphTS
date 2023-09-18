
import { Graph, Vertex } from "./Graph"

const bfs = () => {

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

    const bfs = G.bfs(s, [], [])
    G.showBfs(bfs)
}

const dfs = () => {

    const G = new Graph()

    const a = new Vertex('a')
    const b = new Vertex('a')
    const c = new Vertex('c')
    const d = new Vertex('d')
    const e = new Vertex('e')
    const f = new Vertex('f')

    G.addVertex(a)
    G.addVertex(b)
    G.addVertex(c)
    G.addVertex(d)
    G.addVertex(e)
    G.addVertex(f)

    G.addEdge(a, b, 0)
    G.addEdge(a, d, 0)
    G.addEdge(b, e, 0)
    G.addEdge(d, b, 0)
    G.addEdge(e, d, 0)
    G.addEdge(c, e, 0)
    G.addEdge(c, f, 0)

    const dfs = G.dfs(a, [])
    G.showDfs(dfs)
}

const main = () => {

    const G = new Graph()
    const a = new Vertex('a')
    const b = new Vertex('b')
    const c = new Vertex('c')

    G.addVertex(c)
    G.addVertex(b)

    G.addEdge(b, c, 0)
    G.removeVertex('b')
    G.show()
}

main()