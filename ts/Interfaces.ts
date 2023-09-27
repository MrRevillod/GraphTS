
import { Vertex } from './Graph'

export interface Edge {
    to: Vertex
    weight: number
}

export interface Padre {
    vertex: Vertex
    padre: Vertex | null
}

export interface Nivel {
    vertex: Vertex
    distance: number
}

export class Frontera {

    vertices: Vertex[]

    constructor() {
        this.vertices = []
    }

    push(vertex: Vertex) {
        this.vertices.push(vertex)
    }

    isEmpty() {
        return this.vertices.length === 0
    }
}