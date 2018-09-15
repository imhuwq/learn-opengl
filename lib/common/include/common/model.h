#ifndef LEARN_OPENGL_MODEL_H
#define LEARN_OPENGL_MODEL_H

#include <string>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "common/mesh.h"
#include "common/shader.h"

using namespace std;

class Model {
public:
    explicit Model(const string &path) { LoadModel(path); }

    void Draw(Shader shader);

private:
    vector<Mesh> meshes;
    vector<Texture> textures_loaded;

    string directory;

    void LoadModel(string path);

    void ProcessNode(aiNode *node, const aiScene *scene);

    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

    vector<Texture> LoadMaterialTextures(aiMaterial *material, aiTextureType type, string type_name);
};

#endif //LEARN_OPENGL_MODEL_H
