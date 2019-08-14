#pragma once
class ActivableObject
{
public:
	bool IsActive() const
	{
		return isActive;
	}
	void SetActive(bool active)
	{
		isActive = active;
	}

protected:
	bool isActive = true;
};

