Shader "Custom/02Reflection"
{
    // Properties
    // {
    //     [MainColor] _BaseColor("Base Color", Color) = (1, 1, 1, 1)
    //     [MainTexture] _BaseMap("Base Map", 2D) = "white" {}
    // }

    Properties
    {
        _Horizontal("Horizontal flip", Range(0.0, 1.0)) = 0.2
        _Vertical("Vertical flip", Range(0.0, 1.0)) = 0.4
    }

    SubShader
    {
        Cull Off ZWrite Off ZTest Always // No culling or depth
        Pass 
        {
        Name "Reflex"
        HLSLPROGRAM
        #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Core.hlsl"
        #include "Packages/com.unity.render-pipelines.core/Runtime/Utilities/Blit.hlsl"
        
        #pragma vertex Vert // Funcion Vert en Blit . hlsl
        #pragma fragment frag
        // TEXTURE2D_X ( _BlitTexture );
        SAMPLER (sampler_BlitTexture);

        CBUFFER_START(UnityPerMaterial)
         float _Horizontal;
         float _Vertical;
        CBUFFER_END

        half4 frag (Varyings input) : SV_Target
        {
            // int x = _ScreenParams.x;
            // int y = _ScreenParams.y;
            // int pos = x - (x * _Horizontal)

            float4 text = SAMPLE_TEXTURE2D_X(_BlitTexture, sampler_BlitTexture, input.texcoord);
            float2 uv = input.texcoord;

            if (input.texcoord.x < _Horizontal) 
            {
                uv.x = 1 - input.texcoord.x;
            }

            if (input.texcoord.y < _Vertical) 
            {
                uv.y = 1 - input.texcoord.y;
            }

            return SAMPLE_TEXTURE2D_X(_BlitTexture, sampler_BlitTexture, uv);
            return text;
        }

        ENDHLSL
        }
    }
}