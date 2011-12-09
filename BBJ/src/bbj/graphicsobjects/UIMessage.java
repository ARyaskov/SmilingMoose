/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.*;


/**
 * Абстрактный класс сообщения от одной линии жизни к другой.
 * @author Alexander
 */
abstract public class UIMessage extends SceneItem {
    
    /** Линия жизни - отправитель. */
    protected UILifeLine m_sender;
    
    /** Линия жизни - получатель */ 
    protected UILifeLine m_receiver;
    
    /** Длина линии жизни. */
    protected int m_length;
    
    /** Текст сообщения */
    protected int textX;
            
    /**
     * Запросить отправителя.
     * @return объект ЛЖ
     */
    public UILifeLine getSender(){
        return m_sender;
    }
    
    /**
     * Запросить получателя.
     * @return объект ЛЖ
     */
    public UILifeLine getReceiver(){
        return m_receiver;
    }
    
    /**
     * Запросить длину сообщения
     * @return Длина сообщения
     */
    public int getLength(){
        return m_length;
    }   
    
    public int getTextX(){
        return textX;
    }
    
        /**
     * Отрисовка объекта
     * @param g На чем рисовать
     */
    @Override
    public void paint(Graphics g) {
        
        super.paint(g);
        
        Graphics2D g2 = (Graphics2D)g;
        int endX = m_receiver.x+60;         // Конечная точка
        this.x = m_sender.x+60;             // Начальная точка
        this.h =45;                        // Высота объекта
        this.w = endX - m_sender.x;         // Длина объекта

        
        
        if (m_isSelected)
            g.setColor(Color.red);        // Исходный цвет
        else
            g.setColor(Color.black);        // Цвет при выделении
        
        g2.setStroke(new BasicStroke(2));   // Берем линию потолще
        
        g.drawLine(x, y, x+w-60, y);        // Рисуем линию сообщения
        
        // Рисуем стрелку в зависимости от расположения линии жизни
        if (x < endX){
            endX = m_receiver.x+60;
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
        
        if (m_sender.x <= m_receiver.x){
            setBounds(m_sender.x+60, y-h, m_receiver.x-m_sender.x, h); // Задаем границы
            
            textX= x + (endX - m_sender.x)/2 - 60;
        }
        else{
            setBounds(m_receiver.x+60, y-h, m_sender.x-m_receiver.x, h); // Задаем границы
            
            textX= m_receiver.x + (m_sender.x - m_receiver.x)/2;
        }
        
        g.drawChars(drawedText, 0, java.lang.Math.min(13, m_text.length()), textX, y-10);
        
        if (m_text.length() >= 14)
            g.drawChars(dots, 0, 3, textX+85, y-10);
        
        if (m_isSelected){
            g2.setStroke(new BasicStroke(1));
            g.drawRect(textX-10, y-h+10, 110, h-5);
        }
        
        if (m_isEdit){
            f.repaint();
        }
    }
}
