class App {
	MeshX* mesh;
	float radius;
	float lastX;
	float lastY;
	XMVECTOR quat;
public:
	App();
	~App();
	void Init(const char* fileName);
	void Draw();
	void LButtonDown(float x, float y);
	void LButtonUp(float x, float y);
	void MouseMove(float x, float y);
	void Destroy();
};