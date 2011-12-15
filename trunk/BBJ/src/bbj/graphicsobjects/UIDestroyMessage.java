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
public class UIDestroyMessage extends UIMessage {

    /** Номер экзампляра данного класса на сцене */
    public static int m_localNumber = 0;
    
    /**
     * Основной конструктор
     * @param sender ЛЖ отправитель
     * @param receiver ЛЖ получатель
     * @param y Координата
     */
    UIDestroyMessage(UILifeLine sender, UILifeLine receiver, int y){
        m_sender = sender;
        m_receiver = receiver;
        this.defY = y;
        m_receiver.defH = y+60;
        
        m_receiver.setEnded(true);
        
        m_sender.m_inbox.add(this);
        m_receiver.m_outbox.add(this);
        
        m_focusReceiver = new UIFocusControl(this, false);
        m_focusSender = new UIFocusControl(this, true);
        
        setDefaultName();
        applyScale(getGraphics());
        
        SceneItemListener listener = new SceneItemListener(this);

        this.addMouseListener(listener);
        this.addMouseMotionListener(listener);
        
        this.setToolTipText("Сообщение создания: " + m_text);
    }
    
    /**
     * Отрисовка объекта
     * @param g На чем рисовать
     */
    @Override
    public void paint(Graphics g) {
        
        super.paint(g);
                
        Graphics2D g2 = (Graphics2D)g;     
        this.defX = m_sender.x+60;             // Начальная точка
        int endX = m_receiver.x+60;            // Конечная точка
        this.defH = 45;                        // Высота объекта
        this.defW = endX - this.defX;         // Длина объекта
                
        applyScale(g);
        
        if (m_isSelected)
            g.setColor(Color.red);        // Исходный цвет
        else
            g.setColor(Color.black);        // Цвет при выделении         

        g2.setStroke(new BasicStroke(2));   // Берем линию потолще   
        
        y-=5;
        
        g.drawLine(x, y, endX, y);        // Рисуем линию сообщения

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
                
        
        if (m_isSelected)
            g.setColor(Color.red);        // Исходный цвет
        else
            g.setColor(Color.black);        // Цвет при выделении
        
        // Разбиваем текст на массив символов
        char [] drawedText = m_text.toCharArray();
        char [] dots = {'.','.','.'};
        
        if (m_sender.x <= m_receiver.x){
            setBounds(m_sender.x+60, y-h, m_receiver.x-m_sender.x, h); // Задаем границы
            
            textX= x + (endX - m_sender.x)/2 - 60;
        }
        else{
            setBounds(m_receiver.x+60, y-h, m_sender.x-m_receiver.x, h); // Задаем границы
            
            textX= m_receiver.x + (m_sender.x - m_receiver.x)/2+50;
        }
        
        g.drawChars(drawedText, 0, java.lang.Math.min(13, m_text.length()), textX, y-10);
        
        String buf;
        
        buf = "<<destroy>>";
        drawedText = buf.toCharArray();

        g.drawChars(drawedText, 0, buf.length(), textX, y-22);
  
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
    
    @Override
    protected void setDefaultName() {
        m_text = "Сообщение " + Integer.toString(m_localNumber++);
    }
    
}
