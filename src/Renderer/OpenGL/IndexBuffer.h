#pragma once

class IndexBuffer
{
private:
	uint32_t m_RendererID;
	uint32_t m_Count;
public:
	IndexBuffer(const uint32_t* data, uint32_t count);
	~IndexBuffer();
	void bind() const;
	void unbind() const;

	inline unsigned int getCount() const { return m_Count; }
};