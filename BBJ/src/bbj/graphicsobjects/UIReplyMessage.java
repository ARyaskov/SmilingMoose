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

    UIReplyMessage(UIMessage message){
            
       parentMessage = message;
       m_receiver = parentMessage.m_receiver;
       m_sender = parentMessage.m_sender;
       m_receiver.m_outbox.add(this);
              
       
    
        SceneItemListener listener = new SceneItemListener(this);

        this.addMouseListener(listener);
        this.addMouseMotionListener(listener);
        
        this.setToolTipText("Возврат: " + m_text);
    }
    
    @Override
    public void paint(Graphics g) {
        super.paint(g);
        
        Graphics2D g2 = (Graphics2D)g;
        int endX = parentMessage.m_receiver.x+60;         // Конечная точка
        this.x = parentMessage.m_sender.x+60;             // Начальная точка
        this.h =45;                        // Высота объекта
        this.y = parentMessage.m_focusReceiver.y+parentMessage.m_focusReceiver.h;
        this.w = endX - parentMessage.m_sender.x;         // Длина объекта
        
        if (m_isSelected)
            g.setColor(Color.red);        // Исходный цвет
        else
            g.setColor(Color.black);        // Цвет при выделении
        
        g2.setStroke(new BasicStroke(2.0f,BasicStroke.CAP_BUTT,BasicStroke.JOIN_BEVEL,
                1.0f,new float[]{8.0f,4.0f},0.0f));
            
        y+=5;
        
        g.drawLine(x, y, x+w-60, y);        // Рисуем линию сообщения
        
        // Рисуем стрелку в зависимости от расположения линии жизни
        if (x > endX){
            g.drawLine(x, y, x-7, y+5);
            g.drawLine(x, y, x-7, y-5);
        }
        else{
            g.drawLine(x, y, x+7, y+5);
            g.drawLine(x, y, x+7, y-5);
        }
        
        y-=5;
 
    }
       
    @Override
    protected void setDefaultName() {
        m_text = "Возврат " + Integer.toString(m_localNumber++);
    }
    
}
