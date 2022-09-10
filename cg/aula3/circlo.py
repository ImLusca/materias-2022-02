from operator import imod
import glfw
from OpenGL.GL import *
import OpenGL.GL.shaders
import numpy as np
import random
import math


def main():
    # inicializando janela glfw
    janela = setuparJanela()
    glfw.make_context_current(janela)

    # inicializando listners de teclado e mouse
    glfw.set_key_callback(janela, capturaTeclado)
    glfw.set_mouse_button_callback(janela, capturaMouse)

    # definindo códigos glsl

    vertexCode = """
                attribute vec2 position;
                void main(){
                    gl_Position = vec4(position, 0.0, 1.0);
                }
    """
    fragmentCode = """
                uniform vec4 color;
                void main(){
                    gl_FragColor = color;
                }
    """

    # requisitando slots na GPU
    programa = glCreateProgram()
    vertex = glCreateShader(GL_VERTEX_SHADER)
    fragment = glCreateShader(GL_FRAGMENT_SHADER)

    # associando código aos slots
    glShaderSource(vertex, vertexCode)
    glShaderSource(fragment, fragmentCode)

    # compilando os vertex shaders

    glCompileShader(vertex)
    glCompileShader(fragment)

    # verificando se ocorreu algum erro

    if not glGetShaderiv(vertex, GL_COMPILE_STATUS):
        erro = glGetShaderInfoLog(vertex).decode()
        print(erro)
        raise RuntimeError("Deu ruim compilando Vertex Shader")

    if not glGetShaderiv(fragment, GL_COMPILE_STATUS):
        erro = glGetShaderInfoLog(vertex).decode()
        print(erro)
        raise RuntimeError("Deu ruim compilando o fragment Shader")

    # linkando os shaders com o programa
    glAttachShader(programa, vertex)
    glAttachShader(programa, fragment)

    # buildando o programa
    glLinkProgram(programa)
    if not glGetProgramiv(programa, GL_LINK_STATUS):
        print(glGetProgramInfoLog(programa))
        raise RuntimeError("Deu ruim na linkagem do programa")

    glUseProgram(programa)

    # preparando dados para enviar a gpu

    num_vertices = 16
    pi = 3.14
    counter = 0
    raio = 0.6
    vertices = np.zeros(num_vertices, [("position", np.float32, 2)])

    angle = 0.0
    for counter in range(num_vertices):
        angle += 2*pi/num_vertices
        x = math.cos(angle) * raio
        y = math.sin(angle) * raio
        vertices[counter] = [x, y]

    # requisitando slot da GPU para enviar dados vindos da CPU
    buffer = glGenBuffers(1)
    # setando como buffer padrão
    glBindBuffer(GL_ARRAY_BUFFER, buffer)

    # tacando dados no buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.nbytes, vertices, GL_DYNAMIC_DRAW)
    glBindBuffer(GL_ARRAY_BUFFER, buffer)

    # bindando o atributo de posição
    stride = vertices.strides[0]
    offset = ctypes.c_void_p(0)

    loc = glGetAttribLocation(programa, "position")
    glEnableVertexAttribArray(loc)

    glVertexAttribPointer(loc, 2, GL_FLOAT, False, stride, offset)

    # pegando variavel color
    locColor = glGetUniformLocation(programa, "color")
    R = G = B = 0.4

    # Exibindo janela
    glfw.show_window(janela)

    clock = 0

    while not glfw.window_should_close(janela):
        glfw.poll_events()

        glClear(GL_COLOR_BUFFER_BIT)
        glClearColor(1.0, 1.0, 1.0, 1.0)

        glUniform4f(locColor, R, G, B, 1.0)
        # gl Draw arrays
        glDrawArrays(GL_TRIANGLE_FAN, 0, 16)

        glfw.swap_buffers(janela)

        glClear(GL_COLOR_BUFFER_BIT)
        glClearColor(1.0, 1.0, 1.0, 1.0)

        if clock % 30 == 0:
            R = random.uniform(0,1)
            G = random.uniform(0,1)
            B = random.uniform(0,1)

        glDrawArrays(GL_TRIANGLE_FAN, 0, 8)
        glfw.swap_buffers(janela)
        clock += 1

    glfw.terminate()


def setuparJanela(altura=600, largura=600):
    glfw.init()
    glfw.window_hint(glfw.VISIBLE, glfw.FALSE)
    janela = glfw.create_window(altura, largura, "Pontos", None, None)
    return janela


def capturaTeclado(janela, chave, codigo, acao, mod):
    print('[key event] key=', chave)
    print('[key event] scancode=', codigo)
    print('[key event] action=', acao)
    print('[key event] mods=', mod)


def capturaMouse(janela, botao, acao, mods):
    print('[mouse event] button=', botao)
    print('[mouse event] action=', acao)
    print('[mouse event] mods=', mods)


if __name__ == "__main__":
    main()
