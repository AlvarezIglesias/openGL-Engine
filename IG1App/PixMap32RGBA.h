#ifndef _H_PixMap32RGBA_H
#define _H_PixMap32RGBA_H

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <string>

class PixMap32RGBA
{
public:
	using rgba_color = glm::u8vec4;

	PixMap32RGBA()
	  : data_(nullptr)
	  , width_(0)
	  , height_(0)
	{
	}

	PixMap32RGBA(PixMap32RGBA&& pixmap);
	PixMap32RGBA& operator=(PixMap32RGBA&& pixmap);

	PixMap32RGBA(const PixMap32RGBA& pixmap) = delete;
	PixMap32RGBA& operator=(const PixMap32RGBA& pixmap) = delete;

	~PixMap32RGBA() { free(); }

	void load_bmp24BGR(const std::string& file_name);
	void save_bmp24BGR(const std::string& file_name) const;

	void reserve(GLsizei width, GLsizei height);

	void set_alpha(GLubyte alpha);
	void set_colorkey_alpha(glm::u8vec3 colorKey, GLubyte alpha);

	PixMap32RGBA clone();

	void free();

	GLsizei width() const { return width_; }

	GLsizei height() const { return height_; }

	const rgba_color* data() const { return data_; }

	rgba_color* data() { return data_; }

	bool is_null() const { return data_ == nullptr; }

	const rgba_color& pixel(const GLsizei x, const GLsizei y) const
	{
		return data_[y * width_ + x];
	}

	void set_pixel(const GLsizei x, const GLsizei y, const rgba_color& rgba)
	{
		data_[y * width_ + x] = rgba;
	}

protected:
	void load_headers(std::ifstream& stream,
	                  unsigned int& width,
	                  unsigned int& height) const;
	void save_headers(std::ofstream& stream) const;

	void row_bgr_rgba(char* rowAux, unsigned int r);
	void row_rgba_bgr(char* rowAux, unsigned int r) const;

private:
	rgba_color* data_;
	GLsizei width_;
	GLsizei height_;
};

#endif //_H_PixMap32RGBA_H
