#pragma once

class VertexBuffer
{
private:
	uint32_t m_RendererID;
public:
	VertexBuffer(const void* data, uint32_t size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};