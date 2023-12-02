#pragma once

class SubTriangle
{
public:
	line l1 = line(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
	line l2 = line(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
	line l3 = line(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
};
class Triangle
{
public:
	// Level - on which level it is, Mask - with which level it collides
	int Collision_Level = 0; // -1 - do not collide, >=0 - collision levels
	int Collision_Mask = 0; // -1 - do not collide, >=0 - collision levels
	std::vector <SubTriangle> SubTriangles;
	float roughness = 1.0f;

	line lines[3] = { lines[0] = line(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
					  lines[1] = line(glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
					  lines[2] = line(glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f)) };


	glm::vec2 points[3];
	glm::vec2 midlePosition = glm::vec2(0.0f);
	void Update_Shape()
	{
		SubTriangles.clear();

		midlePosition = points[0] + points[1] + points[2];
		midlePosition /= 3;

		lines[0] = line(points[0], points[1]);
		lines[1] = line(points[1], points[2]);
		lines[2] = line(points[2], points[0]);

		if (!(PointToLineSideCheck(midlePosition, lines[0]) &&
			PointToLineSideCheck(midlePosition, lines[1]) &&
			PointToLineSideCheck(midlePosition, lines[2])))
		{
			glm::vec2 swaper = points[1];
			points[1] = points[2];
			points[2] = swaper;
			lines[0] = line(points[0], points[1]);
			lines[1] = line(points[1], points[2]);
			lines[2] = line(points[2], points[0]);
		}




		for (int i = 0; i < 3; i++)
		{
			SubTriangle temp_tri;
			glm::vec2 p1 = lines[i].P1;
			glm::vec2 p2 = lines[0].P1;
			glm::vec2 p3 = midlePosition;
			if (i + 1 < 3) p2 = lines[i + 1].P1;


			temp_tri.l1 = line(p1, p2);
			temp_tri.l1.width = 1.0f;
			temp_tri.l2 = line(p2, p3);
			temp_tri.l2.width = 0.0f;
			temp_tri.l3 = line(p3, p1);
			temp_tri.l3.width = 0.0f;





			SubTriangles.push_back(temp_tri);

		}

	}

	Triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
	{
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;
		lines[0] = line(p1, p2);
		lines[1] = line(p2, p3);
		lines[2] = line(p3, p1);
		Update_Shape();
	}


	void DrawOutline(glm::vec4 color = glm::vec4(1.0f))
	{
		DrawLine(points[0], points[1], 2.0f, color);
		DrawLine(points[1], points[2], 2.0f, color);
		DrawLine(points[2], points[0], 2.0f, color);
	}
	void DrawNormals()
	{
		glm::vec2 mid1 = points[0] + points[1];
		mid1 *= 0.5f;
		glm::vec2 mid2 = points[1] + points[2];
		mid2 *= 0.5f;
		glm::vec2 mid3 = points[2] + points[0];
		mid3 *= 0.5f;


		DrawLine(mid1, mid1 + lines[0].normal * 50.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		DrawLine(mid2, mid2 + lines[1].normal * 50.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		DrawLine(mid3, mid3 + lines[2].normal * 50.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}
};


// Should be defined clockwise
class polygon
{
public:
	bool lighted = false;
	int Textureid = -1;
	// Level - on which level it is, Mask - with which level it collides
	int Collision_Level = 0; // -1 - do not collide, >=0 - collision levels
	int Collision_Mask = 0; // -1 - do not collide, >=0 - collision levels
	float roughness = 1.0f;
	std::vector <Triangle> triangles;

	std::vector <glm::vec4> colors = { {1.0f,1.0f,1.0f,1.0f} }; // one - for whole poly, two or more for random color, colors_amount=triangles_amount foreach


	//glm::vec2 position = glm::vec2(0.0f);

	std::vector <glm::vec2> points;
	std::vector <glm::vec2> TexturePoints;
	std::vector <glm::ivec3> indexes;

	unsigned int Texture;

	std::vector <glm::vec4> MiscPoints;



	int state = 0;
	void add_Point(glm::vec2 point, bool addindex = false)
	{
		points.push_back(point);

		float aspx = 1.0f * ScreenDivisorX * CameraScale.x;
		float aspy = 1.0f * ScreenDivisorY * CameraScale.y;

		point.x = (point.x - CameraPosition.x) * aspx;
		point.y = (point.y - CameraPosition.y) * aspy;

		TexturePoints.push_back(point);
		if (addindex) 
		{
			if (state == 0)
			{
				glm::ivec3 d;
				d.x = points.size() - 1;
				d.y = points.size() - 1;
				d.z = points.size() - 1;
				indexes.push_back(d);
				state++;
			}
			else if (state == 1)
			{
				indexes[indexes.size() - 1].y = points.size() - 1;
				state++;
			}
			else
			{
				indexes[indexes.size() - 1].z = points.size() - 1;

				glm::ivec3 d;
				d.x = points.size() - 2;
				d.y = points.size() - 1;
				d.z = points.size() - 2;

				indexes.push_back(d);
			}
		}



	}

	void Update_Shape()
	{
		triangles.clear();

		for (int i = 0; i < indexes.size(); i++)
		{
			glm::vec2 p1 = points[indexes[i].x];
			glm::vec2 p2 = points[indexes[i].y];
			glm::vec2 p3 = points[indexes[i].z];

			Triangle t(p1, p2, p3);


			triangles.push_back(t);

		}

	}

	void SaveAs(std::string name)
	{
		std::ofstream SaveFile(name);



		for (int i = 0; i < points.size(); i++)
		{
			SaveFile << "p";
			std::string str = std::to_string(points[i].x);
			SaveFile << str;
			SaveFile << " ";
			str = std::to_string(points[i].y);
			SaveFile << str;
			SaveFile << "\n";
		}
		for (int i = 0; i < indexes.size(); i++)
		{
			SaveFile << "i";
			std::string str = std::to_string(indexes[i].x);
			SaveFile << str;
			SaveFile << " ";
			str = std::to_string(indexes[i].y);
			SaveFile << str;
			SaveFile << " ";
			str = std::to_string(indexes[i].z);
			SaveFile << str;
			SaveFile << "\n";
		}
		for (int i = 0; i < MiscPoints.size(); i++)
		{
			SaveFile << "m";
			std::string str = std::to_string(MiscPoints[i].x);
			SaveFile << str;
			SaveFile << " ";
			str = std::to_string(MiscPoints[i].y);
			SaveFile << str;
			SaveFile << " ";
			str = std::to_string(MiscPoints[i].z);
			SaveFile << str;
			SaveFile << " ";
			str = std::to_string(MiscPoints[i].w);
			SaveFile << str;
			SaveFile << "\n";
		}
		SaveFile.close();
	}


	void Load(std::string name)
	{
		points.clear();
		indexes.clear();
		triangles.clear();
		MiscPoints.clear();
		TexturePoints.clear();
		std::ifstream f(name);
		if (!f.is_open())
			return;
		int i = 0;
		while (!f.eof())
		{
			i++;
			char line[128];
			f.getline(line, 128);
			std::strstream s;
			s << line;

			char junk;
			if (line[0] == 'p')
			{
				glm::vec2 point;
				s >> junk >> point.x >> point.y;
				points.push_back(point);
			}
			if (line[0] == 'i')
			{
				glm::ivec3 index;
				s >> junk >> index.x >> index.y >> index.z;
				indexes.push_back(index);
			}
			if (line[0] == 'm')
			{
				glm::vec4 Misc;
				s >> junk >> Misc.x >> Misc.y >> Misc.z >> Misc.w;
				MiscPoints.push_back(Misc);
			}
		}
		Update_Shape();
	}



	void DrawOutline(glm::vec4 color = glm::vec4(1.0f))
	{
		for (int i = 0; i < points.size(); i++)
		{
			if (i + 1 < points.size())DrawLine(points[i], points[i + 1], 2.0f, color);
			else DrawLine(points[i], points[0], 2.0f, color);
		}

	}
	void DrawTrianglesOutlines(glm::vec4 color = glm::vec4(1.0f))
	{
		for (int i = 0; i < triangles.size(); i++)
		{
			triangles[i].DrawOutline(color);
		}
	}

	void DrawTriangles()
	{
		if (Texture == NULL) 
		{
			if (colors.size() == indexes.size())
				for (int i = 0; i < indexes.size(); i++)
				{
					DrawTriangle(points[indexes[i].x], points[indexes[i].y], points[indexes[i].z], colors[i]);
				}
			if (colors.size() == 1)
				for (int i = 0; i < indexes.size(); i++)
				{
					DrawTriangle(points[indexes[i].x], points[indexes[i].y], points[indexes[i].z], colors[0]);
				}
			if (colors.size() == 0)
				for (int i = 0; i < indexes.size(); i++)
				{
					DrawTriangle(points[indexes[i].x], points[indexes[i].y], points[indexes[i].z], glm::vec4(1.0f));
				}
			if (colors.size() > 0 && colors.size() < indexes.size())
				for (int i = 0; i < indexes.size(); i++)
				{
					int colI = i % colors.size();
					DrawTriangle(points[indexes[i].x], points[indexes[i].y], points[indexes[i].z], colors[colI]);

				}
		}
		else
		{

			if (colors.size() == indexes.size())
				for (int i = 0; i < indexes.size(); i++)
				{
					DrawTexturedTriangle(points[indexes[i].x], points[indexes[i].y], points[indexes[i].z], Texture, colors[i] , TexturePoints[indexes[i].x], TexturePoints[indexes[i].y], TexturePoints[indexes[i].z]);
				}
			else if (colors.size() == 1)
				for (int i = 0; i < indexes.size(); i++)
				{
					DrawTexturedTriangle(points[indexes[i].x], points[indexes[i].y], points[indexes[i].z], Texture, colors[0], TexturePoints[indexes[i].x], TexturePoints[indexes[i].y], TexturePoints[indexes[i].z]);
				}
			else if (colors.size() == 0)
				for (int i = 0; i < indexes.size(); i++)
				{
					DrawTexturedTriangle(points[indexes[i].x], points[indexes[i].y], points[indexes[i].z], Texture, glm::vec4(1.0f), TexturePoints[indexes[i].x], TexturePoints[indexes[i].y], TexturePoints[indexes[i].z]);
				}
			else if (colors.size() > 1 )
				for (int i = 0; i < indexes.size(); i++)
				{
					int colI = i % colors.size();
					DrawTexturedTriangle(points[indexes[i].x], points[indexes[i].y], points[indexes[i].z], Texture, colors[colI], TexturePoints[indexes[i].x], TexturePoints[indexes[i].y], TexturePoints[indexes[i].z]);

				}
		}
	}


};