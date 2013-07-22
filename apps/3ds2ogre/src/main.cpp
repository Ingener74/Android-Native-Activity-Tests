
#include <stdio.h>
#include <vector>
#include <string>
#include <assert.h>
#include <map>
#include <OGRE/OgreVector3.h>

using namespace Ogre;

class Vertex
{
public:
	Vertex(Vector3 pos) : pos(pos), normal(0,0,0) { }
	Vector3 pos;
	Vector3 normal;
};

class Face
{
public:
	Face(int a, int b, int c, unsigned short flags) : a(a), b(b), c(c), flags(flags) { }
	int a, b, c;
	unsigned short flags;
};

class TexMap
{
public:
	TexMap(float u, float v) : u(u), v(v) { }
	float u, v;
};

class TriMesh
{
public:

	std::string name;
	std::string matname;

	std::vector<Vertex> vertexs;
	std::vector<Face> faces;
	std::vector<TexMap> texmaps;
};

class Color
{
public:
	Color() : isSet(false) { }
	bool isSet;

	void set(unsigned char r, unsigned char g, unsigned char b) {
		this->r = r;
		this->g = g;
		this->b = b;
		isSet = true;
	}

	unsigned char r, g, b;
};

class Material
{
public:

	std::string name;
	std::string filename;
	Color ambientColor;
	Color diffuseColor;
	Color specularColor;
	float specularPercent;
};

class Object3d
{
public:

	std::vector<TriMesh> meshes;
	std::vector< ::Material> materials;
};

Object3d *load3DS(char *filename)
{
	FILE *f;
	
	int i;
	unsigned short chunk_id;
	unsigned int chunk_length;

	unsigned char chr;
	unsigned short nelems;

	unsigned short face_flags;
	char name[100], matname[100];

	f = fopen(filename, "rb");
	if (f == NULL) {
		fprintf(stderr, "cannot open input file\n");
		return NULL;
	}

	Object3d *o = new Object3d();

	fseek(f, 0, SEEK_END);
	long filelength = ftell(f);
	fseek(f, 0, SEEK_SET);

	enum { 
		nrgb_none, 
		nrgb_ambient_color,
		nrgb_diffuse_color,
		nrgb_specular_color
	} nrgb = nrgb_none;

	enum {
		npercent_none,
		npercent_specular
	} npercent = npercent_none;

	while (ftell(f) < filelength)
	{
		fread(&chunk_id, 2, 1, f);
		//if ((chunk_id & 0xf000) == 0xa000)
		//	fprintf(stderr, "chunk ID: 0x%x\n", chunk_id); 
		fread(&chunk_length, 4, 1, f);
		//fprintf(stderr, "chunk Length: 0x%x\n", chunk_length);

		switch (chunk_id)
        {
			case 0x4d4d:    // main chunk
				break;    

			case 0x3d3d:  // editor chunk
				break;
			
			case 0x4000:  // object chunk
				i = 0;
				do
				{
					fread(&chr, 1, 1, f);
                    name[i] = chr;
					i++;
                } while(chr != '\0' && i < 20);
				//printf("object: %s\n", name);
				break;

			case 0x4100:  // trimesh chunk
				o->meshes.push_back(TriMesh());
				o->meshes.back().name = name;
				break;
			
			case 0x4110:  // vertex list
				fread(&nelems, sizeof(unsigned short), 1, f);
                //printf("Number of vertices: %d\n", nelems);
                for (i = 0; i < nelems; i++)
                {
					float x, y, z;
					fread(&x, sizeof(float), 1, f);
                    fread (&y, sizeof(float), 1, f);
					fread (&z, sizeof(float), 1, f);
 					//printf("vertex %f %f %f\n", x, y, z);
					//o->meshes.back().vertexs.push_back(Vector3(x, y, z));
					o->meshes.back().vertexs.push_back(Vector3(-x, z, y));    // swap axis system
				}
				break;

			case 0x4120:  // tri list
				fread(&nelems, sizeof(unsigned short), 1, f);
                //printf("Number of triangles: %d\n", nelems); 
                for (i = 0; i < nelems; i++)
                {
					unsigned short a, b, c;
					fread (&a, sizeof(unsigned short), 1, f);
					fread (&b, sizeof(unsigned short), 1, f);
					fread (&c, sizeof(unsigned short), 1, f);
					fread (&face_flags, sizeof(unsigned short), 1, f);
					//printf("tri %d %d %d 0x%x\n", a, b, c, face_flags);
					o->meshes.back().faces.push_back(Face(a, b, c, face_flags));
				}
                break;

			case 0x4130:
				i = 0;
				do
				{
					fread(&chr, 1, 1, f);
					if (chr == ' ')
						chr = '_';
                    matname[i] = chr;
					i++;
                } while(chr != '\0' && i < 20);
				o->meshes.back().matname = matname;
				fread(&nelems, sizeof(unsigned short), 1, f);
				for (i = 0; i < nelems; i++)
				{
					unsigned short idx;
					fread (&idx, sizeof(unsigned short), 1, f);
					// XXX I don't use this.  Ogre requires only one material per submesh.
					//printf("faces uses this material: %d\n", idx);
				}
				break;

			case 0x4140:    // uvs
				fread(&nelems, sizeof(unsigned short), 1, f);
				for (i = 0; i < nelems; i++)
				{
					float u, v;
					fread (&u, sizeof(float), 1, f);
                    fread (&v, sizeof(float), 1, f);
					o->meshes.back().texmaps.push_back(TexMap(u, v));
					//printf("uv: %f %f\n", u, v);
				}
                break;

			case 0xAFFF:  // material chunk
				o->materials.push_back(::Material());
				break;

			case 0xa200:   // texture map
				break;

			case 0xa230:  // bump map
				{
					char bumpmapdata[8];   // ??
					fread(bumpmapdata, 8, 1, f);
					fprintf(stderr, "warning: bump map detected (%s), this will be outputed as a texture.\n",
						o->materials.back().name.c_str());
				}
				break;

			case 0xA000:   // material name chunk
			case 0xA300:   // material filename chunk
				i = 0;
				do
				{
					fread(&chr, 1, 1, f);
					if (chr == ' ')
						chr = '_';
                    matname[i] = chr;
					i++;
                } while(chr != '\0' && i < 20);
				if (chunk_id == 0xa300)
					o->materials.back().filename = matname;
				else
					o->materials.back().name = matname;
				break;

			case 0xA010:
				nrgb = nrgb_ambient_color;
				break;

			case 0xA020:
				nrgb = nrgb_diffuse_color;
				break;

			case 0xA030:
				nrgb = nrgb_specular_color;
				break;

			case 0xA040:
				npercent = npercent_specular;
				break;

			case 0x0011:
				{
					unsigned char r, g, b;
					fread(&r, 1, 1, f);
					fread(&g, 1, 1, f);
					fread(&b, 1, 1, f);
					switch(nrgb) {
						case nrgb_ambient_color:
							o->materials.back().ambientColor.set(r, g, b);
							break;
						case nrgb_diffuse_color:
							o->materials.back().diffuseColor.set(r, g, b);
							break;
						case nrgb_specular_color:
							o->materials.back().specularColor.set(r, g, b);
							break;
						default:
							fprintf(stderr, "unknown rgb %d %d %d\n", r, g, b);
					}
					nrgb = nrgb_none;
				}
				break;

			case 0x0030:
				{
					unsigned short percent;
					fread(&percent, 2, 1, f);
					switch(npercent) {
						case npercent_specular:
							o->materials.back().specularPercent = percent;
							break;
						default:
							fprintf(stderr, "unknown percent %d\n", percent);
					}
				}
				break;

			case 0x0031:
				{
					float percent;
					fread(&percent, sizeof(float), 1, f);
					switch(npercent) {
						case npercent_specular:
							o->materials.back().specularPercent = percent;
							break;
						default:
							fprintf(stderr, "unknown percent %f\n", percent);
					}
				}
				break;
			
			default:   // unknown chunk
				 fseek(f, chunk_length - 6, SEEK_CUR);
        } 
	}

	fclose(f);

	return o;
}

void calculateVertexNormals(Object3d *o)
{
	for (size_t i = 0; i < o->meshes.size(); i++) {
		std::map<size_t, size_t> counts;

		for (size_t j = 0; j < o->meshes[i].vertexs.size(); j++)
			counts[j] = 0;

		for (size_t j = 0; j < o->meshes[i].faces.size(); j++) {
			int a = o->meshes[i].faces[j].a;
			int b = o->meshes[i].faces[j].b;
			int c = o->meshes[i].faces[j].c;

			Vertex &va = o->meshes[i].vertexs[a];
			Vertex &vb = o->meshes[i].vertexs[b];
			Vertex &vc = o->meshes[i].vertexs[c];

			Vector3 normal;

			// calculate normal for face
			normal = (vc.pos - vb.pos).crossProduct(va.pos - vb.pos);
			normal.normalise();

			va.normal += normal;
			vb.normal += normal;
			vc.normal += normal;

			counts[a]++; counts[b]++; counts[c]++;
		}

		for (size_t j = 0; j < o->meshes[i].vertexs.size(); j++)
			o->meshes[i].vertexs[j].normal /= counts[j];
	}
}

bool saveOgre(Object3d *o, const char *filename)
{
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
		fprintf(stderr, "cannot open mesh.xml output file\n");
		return false;
	}

	fprintf(f, "<mesh>\n");
	fprintf(f, "\t<submeshes>\n");

	for (size_t i = 0; i < o->meshes.size(); i++) {
		if (o->meshes[i].faces.size() == 0)
			continue;
		fprintf(f, "\t\t<submesh material=\"%s\" usesharedvertices=\"false\" use32bitindexes=\"%s\">\n", o->meshes[i].matname.c_str(), o->meshes[i].vertexs.size() > 65535 ? "true" : "false");
		fprintf(f, "\t\t\t<faces count=\"%d\">\n", int(o->meshes[i].faces.size()));
		for (size_t j = 0; j < o->meshes[i].faces.size(); j++)
			fprintf(f, "\t\t\t\t<face v1=\"%d\" v2=\"%d\" v3=\"%d\" />\n", 
				o->meshes[i].faces[j].a,
				o->meshes[i].faces[j].b,
				o->meshes[i].faces[j].c);
		fprintf(f, "\t\t\t</faces>\n");
		fprintf(f, "\t\t\t<geometry vertexcount=\"%d\">\n", int(o->meshes[i].vertexs.size()));
		fprintf(f, "\t\t\t\t<vertexbuffer positions=\"true\" normals=\"true\" colours_diffuse=\"false\" texture_coords=\"1\" texture_coords_dimensions_0=\"2\">\n");
		for (size_t j = 0; j < o->meshes[i].vertexs.size(); j++) {
			fprintf(f, "\t\t\t\t\t<vertex>\n");
			fprintf(f, "\t\t\t\t\t\t<position x=\"%f\" y=\"%f\" z=\"%f\" />\n", 
				o->meshes[i].vertexs[j].pos.x, o->meshes[i].vertexs[j].pos.y, o->meshes[i].vertexs[j].pos.z);
			if (j < o->meshes[i].texmaps.size()) {
				fprintf(f, "\t\t\t\t\t\t<texcoord u=\"%f\" v=\"%f\" />\n", 
					o->meshes[i].texmaps[j].u, o->meshes[i].texmaps[j].v);
			} else {
				fprintf(f, "\t\t\t\t\t\t<texcoord u=\"0.0\" v=\"0.0\" />\n");
			}
			fprintf(f, "\t\t\t\t\t\t<normal x=\"%f\" y=\"%f\" z=\"%f\" />\n", 
				o->meshes[i].vertexs[j].normal.x, o->meshes[i].vertexs[j].normal.y, o->meshes[i].vertexs[j].normal.z);
			fprintf(f, "\t\t\t\t\t</vertex>\n");
		}
		fprintf(f, "\t\t\t\t</vertexbuffer>\n");
		fprintf(f, "\t\t\t</geometry>\n");
		fprintf(f, "\t\t</submesh>\n");
	}

	fprintf(f, "\t</submeshes>\n");
	fprintf(f, "</mesh>\n");

	fclose(f);
	return true;
}

bool saveMaterials(Object3d *o, const char *filename)
{
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
		fprintf(stderr, "cannot open material output file\n");
		return false;
	}

	for (size_t i = 0; i < o->materials.size(); i++) {
		fprintf(f, "material %s\n", o->materials[i].name.c_str());
		fprintf(f, "{\n");
		fprintf(f, "\ttechnique\n");
		fprintf(f, "\t{\n");
		fprintf(f, "\t\tpass\n");
		fprintf(f, "\t\t{\n");
		if (o->materials[i].ambientColor.isSet) {
			fprintf(f, "\t\t\tambient %f %f %f\n", 
				o->materials[i].ambientColor.r / 256.0,
				o->materials[i].ambientColor.g / 256.0,
				o->materials[i].ambientColor.b / 256.0);
		}
		if (o->materials[i].diffuseColor.isSet) {
			fprintf(f, "\t\t\tdiffuse %f %f %f\n", 
				o->materials[i].diffuseColor.r / 256.0,
				o->materials[i].diffuseColor.g / 256.0,
				o->materials[i].diffuseColor.b / 256.0);
		}
		if (o->materials[i].specularColor.isSet) {
			fprintf(f, "\t\t\tspecular %f %f %f %f\n", 
				o->materials[i].diffuseColor.r / 256.0,
				o->materials[i].diffuseColor.g / 256.0,
				o->materials[i].diffuseColor.b / 256.0,
				o->materials[i].specularPercent / 100.0);
		}
		if (o->materials[i].filename.size()) {
			fprintf(f, "\t\t\ttexture_unit\n");
			fprintf(f, "\t\t\t{\n");
			fprintf(f, "\t\t\t\ttexture %s\n", o->materials[i].filename.c_str());
			fprintf(f, "\t\t\t}\n");
		}
		fprintf(f, "\t\t}\n");
		fprintf(f, "\t}\n");
		fprintf(f, "}\n");
		fprintf(f, "\n");
	}

	fclose(f);
	return true;
}

int main(int argc, char *argv[])
{
	if (argc < 4) {
		printf("usage: 3ds2ogre <3ds file> <mesh.xml file> <material file>\n");
		return 1;
	}

	fprintf(stderr, "loading 3ds...\n");
	Object3d *o = load3DS(argv[1]);
	if (o == NULL)
		return 1;

	fprintf(stderr, "calculating vertex normals...\n");
	calculateVertexNormals(o);

	fprintf(stderr, "saving ogre mesh...\n");
	if (!saveOgre(o, argv[2])) {
		return 1;
	}

	fprintf(stderr, "saving materials...\n");
	if (!saveMaterials(o, argv[3])) {
		return 1;
	}

	fprintf(stderr, "done.\n");

	return 0;
}


