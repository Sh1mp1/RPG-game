#pragma once


enum buttonState { BTN_IDLE = 0 , BTN_HOVER, BTN_ACTIVE };

namespace gui
{
	class Button;
	class DropDownList;
	class TextureSelector;


	class Button
	{
	private:
		short unsigned buttonState;

		sf::RectangleShape shape;

		sf::Font* font;
		sf::Text text;


		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		short unsigned id;

		void initShape(sf::Vector2f& centrePos, sf::Vector2f& size);
	public:
		Button(sf::Vector2f centrePos, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, const unsigned int characterSize);

		Button(sf::Vector2f centrePos, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, const unsigned int characterSize, 
			   sf::Vector2f rectangleSize, short unsigned id = 0);
		~Button();

		//Accessors
		const bool isPressed() const;
		const sf::FloatRect& getBounds() const;
		const sf::FloatRect& getRectangleBounds() const;
		const std::string getString() const;
		const short unsigned getID() const;

		//Modifiers
		void setText(const std::string text);
		void centreText(const sf::Vector2f& centrePos);

		//Functions
		void update(sf::Vector2f mousePos);
		void render(sf::RenderTarget& target);
		void render(sf::RenderTarget& target, const bool& drawShape);
	};

	/*
	DropDownList------------------------------------------------------------------------------------------------------------------------------------------------------------------
	*/

	class DropDownList
	{
	private:
		sf::Font& font;
		gui::Button* activeElement;

		sf::Vector2f centrePos;

		std::vector<gui::Button*> list;
		bool showList;
		bool isMousePressed;

		//Initialization functions
		void initList(sf::Vector2f pos, std::vector<std::string> list, unsigned int defaultIndex = 0);

	public:
		DropDownList(sf::Vector2f pos, sf::Font& font, std::vector<std::string> list, unsigned int defaultIndex);
		~DropDownList();

		//Accessors
		const short unsigned getActiveElementID() const;
		

		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:
		float gridSize;
		bool isActive;

		sf::RectangleShape bounds;	//The big rectangle containing the entire tile sheet

		sf::Sprite sheet;

		sf::RectangleShape selectorRect;	//The outline that shows the current active tile

		sf::Vector2u mousePosGrid;

		sf::IntRect textureRect;

		

		//Initialization functions
		void initRect(float x, float y, float width, float height);
		void initSprite(float x, float y, sf::Texture* texture_sheet);
	public:
		TextureSelector(float x, float y, float width, float height, sf::Texture* texture_sheet, float grid_size);
		~TextureSelector();

		//Accessors
		const bool& getIsActive() const;

		//Functions
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);
	};
}

