#pragma once

#include "view/icon/Icon.h"
#include <memory>

class Viewable {
public:
	using Ptr = std::shared_ptr<Viewable>;
	// Ptr create() {
	// 	return Ptr(new Viewable());
	// }

protected:
	Icon icon_;

public:
	size_t icon_width() const;
	size_t icon_height() const; 

	const Icon& getIcon() const;
	virtual const Pos2& getPosition() const = 0;

	void setIcon(const Icon&);
	virtual void setPosition(const Pos2&) = 0;
	
};