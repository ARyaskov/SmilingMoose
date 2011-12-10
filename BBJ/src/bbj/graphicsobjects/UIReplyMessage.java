/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.*;

/**
 *
 * @author Alexander
 */
public class UIReplyMessage extends UIMessage {

    /** Номер экзампляра данного класса на сцене */
    public static int m_localNumber = 0;
    
    /** Сообщение родитель */
    public UIMessage parentMessage;

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
        
        g2.setStroke(new BasicStroke(1.0f,BasicStroke.CAP_BUTT,BasicStroke.JOIN_BEVEL,
                1.0f,new float[]{8.0f,4.0f},0.0f));
              
        g.drawLine(x, y, x+w-60, y);        // Рисуем линию сообщения
        
        // Рисуем стрелку в зависимости от расположения линии жизни
        if (x > endX){
            endX = m_receiver.x+60;
            g.drawLine(endX, y, endX-7, y+5);
            g.drawLine(endX, y, endX-7, y-5);
        }
        else{
            g.drawLine(endX, y, endX+7, y+5);
            g.drawLine(endX, y, endX+7, y-5);
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
        
        String buf;
                    
        if (m_text.length() >= 14)
            g.drawChars(dots, 0, 3, textX+85, y-10);
        
        if (m_isSelected){
            g2.setStroke(new BasicStroke(1));
            g.setColor(Color.red);
            g.drawRect(textX-10, y-h+10, 110, h-5);
        }
        
        if (m_isEdit){
            f.repaint();
        }
    }
    
    
    
    
    @Override
    protected void setDefaultName() {
        m_text = "Возврат " + Integer.toString(m_localNumber++);
    }
    
}
