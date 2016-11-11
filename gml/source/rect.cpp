#include "../include/gmlrect.h"

namespace gml
{
	bool rect::operator==(const rect& other) const
	{
		if (this == &other)
		{
			return true;
		}
		return (m_pos == other.m_pos) && (m_size == other.m_size);
	}

	int rect::left() const
	{
		return m_pos.x;
	}

	int rect::right() const
	{
		return left() + width();
	}

	int rect::top() const
	{
		return m_pos.y;
	}

	int rect::bottom() const
	{
		return top() + height();
	}

	int rect::width() const
	{
		return m_size.x;
	}

	int rect::height() const
	{
		return m_size.y;
	}

	coord rect::center() const
	{
		return coord((left() + right()) / 2, (top() + bottom()) / 2);
	}

	coord rect::position() const
	{
		return m_pos;
	}

	coord rect::size() const
	{
		return m_size;
	}

	void rect::set_width(int w)
	{
		m_size.x = w > 0 ? w : 0;
	}

	void rect::set_height(int h)
	{
		m_size.y = h > 0 ? h : 0;
	}

	void rect::set_left(int x)
	{
		m_pos.x = x;
	}


	void rect::set_right(int x)
	{
		m_size.x = x - left();
		if (m_size.x < 0) m_size.x = 0;
	}

	void rect::set_top(int y)
	{
		m_pos.y = y;
	}

	void rect::set_bottom(int y)
	{
		m_size.y = y - top();
		if (m_size.y < 0) m_size.y = 0;
	}

	void rect::set_pos(int x, int y)
	{
		set_left(x);
		set_top(y);
	}

	void rect::set_pos(const coord& pos)
	{
		set_pos(pos.x, pos.y);
	}

	void rect::set_size(int w, int h)
	{
		set_width(w);
		set_height(h);
	}

	void rect::set_size(const coord& size)
	{
		return set_size(size.x, size.y);
	}

	bool rect::contains(int x, int y) const
	{
		return !(x < left() || x > right() || y < top() || y > bottom());
	}

	bool rect::contains(const coord& point) const
	{
		return contains(point.x, point.y);
	}

	int get_intersect_number(const rect& container, const rect& to_check)
	{
		int intersect_other = 0;

		if (container.contains(to_check.left(), to_check.top()))
			intersect_other++;
		if (container.contains(to_check.left(), to_check.bottom()))
			intersect_other++;
		if (container.contains(to_check.right(), to_check.top()))
			intersect_other++;
		if (container.contains(to_check.right(), to_check.bottom()))
			intersect_other++;

		return intersect_other;
	}

	it_mode rect::hit_test(const rect& other) const
	{
		if (*this == other)
		{
			return it_same;
		}

		int intersect_other = get_intersect_number(other, *this);
		if (intersect_other == 4)
		{
			return it_inside;
		}
		// Impossible 3.
		else if (intersect_other == 2 || intersect_other == 1)
		{
			return it_intersect;
		}
		else
		{
			intersect_other = get_intersect_number(*this, other);
			if (intersect_other == 4)
			{
				return it_contain;
			}
			// Impossible 3.
			else if (intersect_other == 2) // Impossible 1
			{
				return it_intersect;
			}
			else
			{
				return it_none;
			}
		}
	}

	void rect::move(int offsetx, int offsety)
	{
		m_pos.move(offsetx, offsety);
	}

	void rect::enlarge(int offsetw, int offseth)
	{
		m_size.move(offsetw, offseth);
		if (m_size.x < 0) m_size.x = 0;
		if (m_size.y < 0) m_size.y = 0;
	}
}