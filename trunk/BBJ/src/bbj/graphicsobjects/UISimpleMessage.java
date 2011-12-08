/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;

/**
 *
 * @author Alexander
 */
public class UISimpleMessage extends UIMessage {
    
    /**
     * Основной конструктор
     * @param sender Отправитель
     * @param receiver Получатель
     */
    public UISimpleMessage(UILifeLine sender, UILifeLine receiver, int y, String text ){
        m_sender = sender;
        m_receiver = receiver;
        this.y = y;
        m_text = text;
    }

    /**
     * Отрисовка объекта
     * @param g На чем рисовать
     */
    @Override
    public void paint(Graphics g) {
        Graphics2D g2= (Graphics2D)g;
        
        int endX = m_receiver.x+60;         // Конечная точка
        this.x = m_sender.x+60;             // Начальная точка
        this.h = 25;                        // Высота объекта
        this.w = endX - m_sender.x;         // Длина объекта

        setBounds(x, y, w, h);              // Задаем границы
        
        if (m_isSelected)
            g.setColor(Color.red);        // Исходный цвет
        else
            g.setColor(Color.black);        // Цвет при выделении
        
        g2.setStroke(new BasicStroke(2));   // Берем линию потолще
        
        g.drawLine(x, y, x+w-60, y);        // Рисуем линию сообщения
        
        // Рисуем стрелку в зависимости от расположения линии жизни
        if (x > endX){
            endX = m_sender.x+60;
            g.drawLine(endX, y, endX-7, y+5);
            g.drawLine(endX, y, endX-7, y-5);
        }
        else{
            g.drawLine(x, y, x+7, y+5);
            g.drawLine(x, y, x+7, y-5);
        }
        
        // Разбиваем текст на массив символов
        char [] drawedText = m_text.toCharArray();
        char [] dots = {'.','.','.'};
        
        int textX;
        if (m_sender.x <= m_receiver.x)
            textX= x + (endX - m_sender.x)/2 - 60;
        else
            textX= m_receiver.x + (m_sender.x - m_receiver.x)/2;
        
        g.drawChars(drawedText, 0, java.lang.Math.min(13, m_text.length()), textX, y-10);
        
        if (m_text.length() >= 14)
            g.drawChars(dots, 0, 3, textX+85, y-10);
        
    }
    
    
}
