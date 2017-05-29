#include "TelaInstructions.h"

TelaInstructions::TelaInstructions()
{
}

TelaInstructions::~TelaInstructions()
{
}

void TelaInstructions::inicializar()
{
	// ATRIBUTO: bg
	if (!gRecursos.carregouSpriteSheet("instructions"))
	{
		gRecursos.carregarSpriteSheet("instructions", "imagens/spr_instructions.png");
	}
	bg.setSpriteSheet("instructions");
}

void TelaInstructions::draw()
{
	executar();
	desenhar();
}

void TelaInstructions::executar()
{
}

void TelaInstructions::desenhar()
{
	bg.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
}
