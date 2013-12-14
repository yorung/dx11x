class App {
	MeshX* mesh;
	float radius;
public:
	App();
	~App();
	void Init(const char* fileName);
	void Draw();
	void Destroy();
};