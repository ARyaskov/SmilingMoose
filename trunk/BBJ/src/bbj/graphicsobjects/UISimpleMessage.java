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
public class UISimpleMessage extends UIMessage {
    
    /** Номер экзампляра данного класса на сцене */
    public static int m_localNumber = 0;
    
    /**
     * Основной конструктор
     * @param sender Отправитель
     * @param receiver Получатель
     */
    public UISimpleMessage(UILifeLine sender, UILifeLine receiver, int y){
        m_sender = sender;
        m_receiver = receiver;
        
        m_sender.m_inbox.add(this);
        m_receiver.m_outbox.add(this);
        
        m_focusReceiver = new UIFocusControl(this, false);
        m_focusSender = new UIFocusControl(this, true);
        
        this.defY = y;
        this.h =45;                        // Высота объекта
        
        //applyScale(getGraphics());
        
        setDefaultName();
        
        SceneItemListener listener = new SceneItemListener(this);

        this.addMouseListener(listener);
        this.addMouseMotionListener(listener);
//        this.addKeyListener(listener);
        
        this.setToolTipText("Сообщение: " + m_text);
    }
    
     /**
     * Отрисовка объекта
     * @param g На чем рисовать
     */
    @Override
    public void paint(Graphics g) {
        
        super.paint(g);
                
        Graphics2D g2 = (Graphics2D)g;
        int endX = m_receiver.x+zoom(60);         // Конечная точка
         
        this.x = m_sender.x+zoom(60);             // Начальная точка
        this.w = endX - m_sender.x;         // Длина объекта
        this.y = this.defY;
      // applyScale(getGraphics());
        
        if (m_isSelected)
            g.setColor(Color.red);        // Исходный цвет
        else
            g.setColor(Color.black);        // Цвет при выделении
        
        g2.setStroke(new BasicStroke(2));   // Берем линию потолще
        
        y-=5;
        
        g.drawLine(x, y, x+w-zoom(60), y);        // Рисуем линию сообщения
        
        // Рисуем стрелку в зависимости от расположения линии жизни
        if (x < endX){
            g.drawLine(endX, y, endX-7, y+5);
            g.drawLine(endX, y, endX-7, y-5);
        }
        else{
            g.drawLine(endX, y, endX+7, y+5);
            g.drawLine(endX, y, endX+7, y-5);
        }
        y+=5;
        m_focusReceiver.paint(g);
        m_focusSender.paint(g);
        
        // Разбиваем текст на массив символов
        char [] drawedText = m_text.toCharArray();
        char [] dots = {'.','.','.'};
        
        if (m_sender.x <= m_receiver.x){
            setBounds(m_sender.x+zoom(60), y-h, m_receiver.x-m_sender.x, h); // Задаем границы
            
            textX= x + (endX - m_sender.x)/2 - zoom(60);
        }
        else{
            setBounds(m_receiver.x+zoom(60), y-h, m_sender.x-m_receiver.x, h); // Задаем границы
            
            textX= m_receiver.x + (m_sender.x - m_receiver.x)/2;
        }
        
        g.drawChars(drawedText, 0, java.lang.Math.min(13, m_text.length()), textX, y-zoom(10));
        
        String buf;
                    
        if (m_text.length() >= 14)
            g.drawChars(dots, 0, 3, textX+zoom(85), y-zoom(10));
        
        if (m_isSelected){
            g2.setStroke(new BasicStroke(1));
            g.setColor(Color.red);
            g.drawRect(textX-zoom(10), y-h+zoom(10), zoom(110), h-zoom(5));
        }
        
        if (m_isEdit){
            f.repaint();
        }
    }
    
    @Override
    protected void setDefaultName() {
        m_text = "Сообщение " + Integer.toString(m_localNumber++);
    }
     
}
