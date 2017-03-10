#pragma once
class RenderManager
{
private:
	RenderManager(void);
	~RenderManager(void);

	static RenderManager* render;

public:
	RenderManager& getInstance()
	{
		if (!render)
		{
			render = new RenderManager();
			if (!render)
			{
				//TODO: error
			}
		}
		return *render;
	}
};

