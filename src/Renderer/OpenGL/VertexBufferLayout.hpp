#pragma once 
#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
	uint32_t count;
	uint32_t type;
	unsigned char normalized;

	static uint32_t GetSizeOfType(uint32_t type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
			break;
		case GL_UNSIGNED_INT:	return 4;
			break;
		case GL_UNSIGNED_BYTE:	return 1;
			break;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
		:	m_Stride(0){}

	~VertexBufferLayout();

	template<typename T>
	void Push(uint32_t count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(uint32_t count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline const uint32_t GetStride() const { return m_Stride; }

private:
	std::vector<VertexBufferElement> m_Elements;
	uint32_t m_Stride;
};