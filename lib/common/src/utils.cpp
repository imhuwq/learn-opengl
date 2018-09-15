#include "common/utils.h"

using namespace std;

unsigned int TextureFromFile(const string &path, const string &directory) {
    unsigned int texture_id;
    string texture_path = directory + "/" + path;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nr_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &nr_channels, 0);
    if (data) {
        GLenum format = GL_RGB;
        if (nr_channels == 1) format = GL_RED;
        else if (nr_channels == 3) format = GL_RGB;
        else if (nr_channels == 4) format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);
    return texture_id;
}