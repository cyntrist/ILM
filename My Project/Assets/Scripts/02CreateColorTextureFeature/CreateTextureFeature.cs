using Unity.VisualScripting;
using UnityEditor;
using UnityEngine;
using UnityEngine.Rendering.Universal;

public class CreateTextureFeature : ScriptableRendererFeature
{
    [SerializeField]
    private Color m_ColorRelleno;

    [SerializeField]
    private RenderPassEvent _renderPassEvent;

    CreateTexturePass m_Pass;

    // se llama a esto cada vez que se cambia algo (incluyendo en su creación)
    public override void Create()
    {
        m_Pass = new CreateTexturePass();
        m_Pass.renderPassEvent = _renderPassEvent;
    }

    // se llama una vez por frame
    public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData)
    {
        m_Pass.Setup(m_ColorRelleno);
        renderer.EnqueuePass(m_Pass);
    }
}
