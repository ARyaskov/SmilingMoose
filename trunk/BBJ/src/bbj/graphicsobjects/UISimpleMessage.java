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
        
        this.y = y;
        
        setDefaultName();
        
        SceneItemListener listener = new SceneItemListener(this);

        this.addMouseListener(listener);
        this.addMouseMotionListener(listener);
        
        this.setToolTipText("Сообщение: " + m_text);
    }
    
    @Override
    protected void setDefaultName() {
        m_text = "Сообщение " + Integer.toString(m_localNumber++);
    }
     
}
