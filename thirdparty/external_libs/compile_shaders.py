import os;

os.system("glslc shaders/vertex.vert -o ../engine/Shaders/vertex.spv")
os.system("glslc shaders/fragment.frag -o ../engine/Shaders/fragment.spv")