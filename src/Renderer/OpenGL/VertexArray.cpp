#include "VertexArray.hpp"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl)
{
	bind();
	vb.bind();
	const auto& elements = vbl.GetElements();
	uint32_t offset = 0;

	for (uint32_t i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, vbl.GetStride(), (const void*)0);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::bind() const		{	glBindVertexArray(m_RendererID);	}
void VertexArray::unbind() const	{	glBindVertexArray(0);	}

